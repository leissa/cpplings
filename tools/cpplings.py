#!/usr/bin/env python3
import sys
import json
import time
import pathlib
import subprocess
import os
from ascii import print_ascii

ROOT = pathlib.Path(__file__).resolve().parent.parent
BUILD = ROOT / "build"
CONFIG_FILE = ROOT / "exercises.json"


def load_exercises():
    with open(CONFIG_FILE, "r", encoding="utf-8") as f:
        return json.load(f)


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
    for ex in get_targets():
        print(ex["name"])


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
    for ex in load_exercises():
        name = ex["name"]
        print(f"\n== {name} ==")

        try:
            cmake_build(name)
            subprocess.check_call([str(BUILD / name)])
        except subprocess.CalledProcessError:
            print(f"\n❌ Failed: {name}")
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
    print_ascii()

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


def usage():
    print("usage:")
    print("  cpplings list")
    print("  cpplings run <exercise>")
    print("  cpplings verify")
    print("  cpplings watch <exercise>")
    print("  cpplings watch-all")
    sys.exit(1)


def main():
    if len(sys.argv) < 2:
        usage()

    cmd = sys.argv[1]
    cmake_configure()

    if cmd == "list":
        list_exercises()
    elif cmd == "run":
        if len(sys.argv) != 3:
            usage()
        run_exercise(sys.argv[2])
    elif cmd == "verify":
        verify()
    elif cmd == "watch":
        if len(sys.argv) != 3:
            usage()
        watch(sys.argv[2])
    elif cmd == "watch-all":
        if len(sys.argv) != 2:
            usage()
        watch_all()
    else:
        usage()


if __name__ == "__main__":
    main()
