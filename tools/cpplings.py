#!/usr/bin/env python3

import argparse
import sys
import time
import pathlib
import subprocess
import os
from ascii import print_ascii

ROOT = pathlib.Path(__file__).resolve().parent.parent
BUILD = ROOT / "build"
CONFIG_FILE = ROOT / "exercises.json"


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
    for ex in get_targets():
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


def watch_all():
    targets = get_targets()
    mtimes = {}  # name -> last mtime
    print(targets)
    current_idx = 0

    while current_idx < len(targets):
        name = targets[current_idx]
        # glob for the matching .cpp under exercises/
        matches = list(ROOT.glob(f"exercises/**/{name}.cpp"))
        if not matches:
            print(name + "does not match any exercise. Skipping")
            current_idx += 1
            continue

        # FIXME this is copy & paste from above
        mtime = matches[0].stat().st_mtime
        if mtimes.get(name) != mtime:
            mtimes[name] = mtime
            print("\n[watch] change detected")

            try:
                print(name)
                cmake_build(name)
                run_binary(name)
                print("[watch] ✅ pass")
                current_idx += 1
            except subprocess.CalledProcessError:
                print("[watch] ❌ fail")

        time.sleep(0.4)


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
    args = parser.parse_args()

    cmake_configure()

    if args.cmd == "list":
        list_exercises()
    elif args.cmd == "run":
        run_exercise(args.exercise)
    elif args.cmd == "verify":
        verify()
    elif args.cmd == "watch":
        watch(args.exercise)
    elif args.cmd == "watch-all":
        watch_all()

if __name__ == "__main__":
    main()
