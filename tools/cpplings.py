#!/usr/bin/env python3
import json
import os
import pathlib
import subprocess
import sys
import time

ROOT = pathlib.Path(__file__).resolve().parent.parent
BUILD = ROOT / "build"
CONFIG_FILE = ROOT / "exercises.json"

env = os.environ.copy()
env["ASAN_OPTIONS"] = (
    "halt_on_error=1:abort_on_error=1:exitcode=1:detect_stack_use_after_return=1:check_initialization_order=1:strict_init_order=1:detect_leaks=1"
)
env["UBSAN_OPTIONS"] = "halt_on_error=1:print_stacktrace=1:report_error_type=1"


def load_exercises():
    with open(CONFIG_FILE, "r", encoding="utf-8") as f:
        return json.load(f)


def cmake_configure():
    BUILD.mkdir(exist_ok=True)
    subprocess.check_call(["cmake", "-S", str(ROOT), "-B", str(BUILD)])


def cmake_build(target=None):
    cmd = ["cmake", "--build", str(BUILD)]
    if target:
        cmd += ["--target", target]
    subprocess.check_call(cmd)


def find_exercise(name):
    for ex in load_exercises():
        if ex["name"] == name:
            return ex
    return None


def list_exercises():
    for ex in load_exercises():
        print(ex["name"])


def run_exercise(name):
    ex = find_exercise(name)
    if not ex:
        print(f"exercise not found: {name}")
        sys.exit(1)

    print(f"[+] Building {name}")
    cmake_build(name)

    print(f"[+] Running {name}")
    subprocess.check_call([str(BUILD / name)], env=env)


def verify():
    for ex in load_exercises():
        name = ex["name"]
        print(f"\n== {name} ==")

        try:
            cmake_build(name)
            subprocess.check_call([str(BUILD / name)], env=env)
        except subprocess.CalledProcessError:
            print(f"\n❌ Failed: {name}")
            sys.exit(1)

    print("\n✅ All exercises passed.")


def watch(name):
    ex = find_exercise(name)
    if not ex:
        print(f"exercise not found: {name}")
        sys.exit(1)

    path = ROOT / ex["path"]
    if not path.exists():
        print(f"exercise file missing: {path}")
        sys.exit(1)

    print(f"[watch] watching {name} ({path})")

    last_mtime = 0
    while True:
        mtime = path.stat().st_mtime
        if mtime != last_mtime:
            last_mtime = mtime
            print("\n[watch] change detected")

            try:
                cmake_build(name)
                subprocess.check_call([str(BUILD / name)], env=env)
                print("[watch] ✅ pass")
            except subprocess.CalledProcessError:
                print("[watch] ❌ fail")

        time.sleep(0.4)


def usage():
    print("usage:")
    print("  cpplings list")
    print("  cpplings run <exercise>")
    print("  cpplings verify")
    print("  cpplings watch <exercise>")
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
    else:
        usage()


if __name__ == "__main__":
    main()
