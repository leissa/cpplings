#!/usr/bin/env bash
set -euo pipefail

REPO_URL="git@gitlab.gwdg.de:leissa/cpplings.git"
TARGET_DIR="cpplings"
BRANCH="master"

echo "[cpplings] Installing into ./$TARGET_DIR"

if ! command -v git >/dev/null 2>&1; then
    echo "[cpplings] ERROR: git is not installed."
    exit 1
fi

if [ -d "$TARGET_DIR" ]; then
    echo "[cpplings] ERROR: ./$TARGET_DIR already exists."
    exit 1
fi

echo "[cpplings] Cloning repository..."
git clone --recursive --branch "$BRANCH" "$REPO_URL" "$TARGET_DIR"
echo "✅ Done."
