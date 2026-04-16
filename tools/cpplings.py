#!/usr/bin/env python3

import argparse
import sys
import time
import pathlib
import subprocess
import os
import threading
import json
from ascii import print_ascii

ROOT = pathlib.Path(__file__).resolve().parent.parent
BUILD = ROOT / "build"

CACHE_FILE = BUILD / "cpplings_cache.json"


def load_cache():
    try:
        data = json.loads(CACHE_FILE.read_text())
        targets = get_targets()
        # validate cached names still exist
        data["skipped"] = [s for s in data.get("skipped", []) if s in targets]
        idx = data.get("current_idx", 0)
        data["current_idx"] = max(0, min(idx, len(targets) - 1))
        return data
    except:
        return {"current_idx": 0, "skipped": []}


def reset_state():
    CACHE_FILE.unlink(missing_ok=True)
    targets = get_targets()
    cache = load_cache()
    return init_state(cache, targets)


def save_cache(state):
    with state["lock"]:
        data = {
            "current_idx": state["current_idx"],
            "skipped": state["skipped"],
        }
    CACHE_FILE.write_text(json.dumps(data))


def init_state(cache, targets):
    return {
        "current_idx": cache["current_idx"],
        "targets": targets,
        "mtimes": {},
        "skipped": cache["skipped"],
        "lock": threading.Lock(),
    }


def get_targets():
    output = subprocess.check_output(
        ["cmake", "--build", str(BUILD), "--target", "help"], stderr=subprocess.DEVNULL
    ).decode()
    return [
        pathlib.Path(line.strip().lstrip(". ")).stem
        for line in output.splitlines()
        if "exercises/" in line and line.strip().endswith(".o")
    ]


def cmake_configure():
    BUILD.mkdir(exist_ok=True)
    subprocess.check_call(["cmake", "-S", str(ROOT), "-B", str(BUILD)])


def cmake_build(target=None):
    cmd = ["cmake", "--build", str(BUILD)]
    if target:
        cmd += ["--target", target]
    subprocess.check_call(cmd)


def run_binary(name):
    env = os.environ.copy()
    env["UBSAN_OPTIONS"] = "halt_on_error=1"
    env["ASAN_OPTIONS"] = "halt_on_error=1"
    subprocess.check_call([str(BUILD / name)], env=env)


def find_exercise(name):
    for _ in get_targets():
        matches = list(ROOT.glob(f"exercises/**/{name}.cpp"))
        if len(matches) == 1:
            return matches[0]
    return None


def list_exercises():
    print("== Exercises: ==")
    for ex in get_targets():
        print(ex)


def run_exercise(name):
    ex = find_exercise(name)
    if not ex:
        print(f"exercise not found: {name}")
        sys.exit(1)

    print(f"[+] Building {name}")
    cmake_build(name)

    print(f"[+] Running {name}")
    subprocess.check_call([str(BUILD / name)])


def verify():
    for ex in get_targets():
        print(f"\n== {ex} ==")

        try:
            cmake_build(ex)
            subprocess.check_call([str(BUILD / ex)])
        except subprocess.CalledProcessError:
            print(f"\n❌ Failed: {ex}")
            sys.exit(1)

    print("\n✅ All exercises passed.")


def watch(name):
    ex = find_exercise(name)
    if not ex:
        print(f"exercise not found: {name}")
        sys.exit(1)

    print(f"[watch] watching {name} ({ex})")

    last_mtime = 0
    while True:
        mtime = ex.stat().st_mtime
        if mtime != last_mtime:
            last_mtime = mtime
            print("\n[watch] change detected")

            try:
                cmake_build(name)
                run_binary(name)
                print("[watch] ✅ pass")
            except subprocess.CalledProcessError:
                print("[watch] ❌ fail")

        time.sleep(0.4)


def watcher_thread(state):
    while True:
        with state["lock"]:
            idx = state["current_idx"]
            targets = state["targets"]

        if idx >= len(targets):
            print("\n🎉 All exercises passed!")
            return

        name = targets[idx]
        matches = list(ROOT.glob(f"exercises/**/{name}.cpp"))
        if not matches:
            with state["lock"]:
                state["current_idx"] += 1
            continue

        mtime = matches[0].stat().st_mtime
        with state["lock"]:
            last = state["mtimes"].get(name)
        save_cache(state)

        if mtime != last:
            with state["lock"]:
                state["mtimes"][name] = mtime
            print(f"\n[watch] change detected in {name}")
            print(
                f"\n\033[1;38;2;255;165;0m[{idx + 1}/{len(targets)}] === {name} ===\033[0m"
            )
            try:
                cmake_build(name)
                run_binary(name)
                print("[watch] ✅ pass")
                with state["lock"]:
                    state["current_idx"] += 1
            except subprocess.CalledProcessError:
                print("[watch] ❌ fail")
                print("options: (n)ext  (p)rev (g)oto <name|number> (r)eset (q)uit")

        time.sleep(0.4)


def watch_all():
    targets = get_targets()
    cache = load_cache()

    if cache["skipped"]:
        print(f"⚠️  Skipped exercises: {', '.join(cache['skipped'])}")
    state = init_state(cache, targets)

    t = threading.Thread(target=watcher_thread, args=(state,), daemon=True)
    t.start()

    while t.is_alive():
        key = input().strip()
        parts = key.split()

        if not parts:
            continue

        with state["lock"]:
            idx = state["current_idx"]

        match parts[0]:
            case "n":
                with state["lock"]:
                    state["current_idx"] = min(idx + 1, len(targets) - 1)
                    state["skipped"].append(targets[idx])
                    state["mtimes"].pop(targets[idx], None)
                save_cache(state)
            case "p":
                with state["lock"]:
                    prev = max(idx - 1, 0)
                    state["mtimes"].pop(targets[idx], None)
                    state["mtimes"].pop(targets[prev], None)
                    state["current_idx"] = prev
                save_cache(state)
            case "g":
                if len(parts) < 2:
                    print("usage: g <name|number>")
                    continue
                arg = parts[1]
                try:
                    new_idx = int(arg) - 1  # 1-based
                    if not 0 <= new_idx < len(targets):
                        print(f"index out of range: 1–{len(targets)}")
                        continue
                except ValueError:
                    if arg not in targets:
                        print(f"exercise not found: {arg}")
                        continue
                    new_idx = targets.index(arg)
                with state["lock"]:
                    state["mtimes"].pop(targets[new_idx], None)
                    state["current_idx"] = new_idx
                save_cache(state)

            case "r":
                with state["lock"]:
                    state["current_idx"] = 0
                    state["skipped"] = []
                    state["mtimes"] = {}
                save_cache(state)
            case "q":
                return
            case _:
                continue


def main():
    print_ascii()

    # default behavior: cpplings == cpplings watch-all
    if len(sys.argv) == 1:
        sys.argv.append("watch-all")

    parser = argparse.ArgumentParser(prog="cpplings")
    subparsers = parser.add_subparsers(dest="cmd", required=True)
    subparsers.add_parser("list", help="List available exercises")
    run_parser = subparsers.add_parser("run", help="Run a specific exercise")
    run_parser.add_argument("exercise", help="Exercise name to run")
    subparsers.add_parser("verify", help="Verify all exercises")
    watch_parser = subparsers.add_parser("watch", help="Watch a specific exercise")
    watch_parser.add_argument("exercise", help="Exercise name to watch")
    subparsers.add_parser("watch-all", help="Watch all exercises (default)")
    subparsers.add_parser("reset", help="Reset progress")
    args = parser.parse_args()

    cmake_configure()

    match args.cmd:
        case "list":
            list_exercises()
        case "run":
            run_exercise(args.exercise)
        case "verify":
            verify()
        case "watch":
            watch(args.exercise)
        case "watch-all":
            watch_all()
        case "reset":
            CACHE_FILE.unlink(missing_ok=True)
            print("✅ Progress reset.")


if __name__ == "__main__":
    main()
