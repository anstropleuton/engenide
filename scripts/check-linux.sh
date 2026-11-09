#!/usr/bin/env bash
set -u
cd "$(dirname "$0")/.."

PRESETS=(linux-gcc-debug linux-gcc-release linux-clang-debug linux-clang-release linux-clang-debug-tidy)
[[ $# -gt 0 ]] && PRESETS=("$@")

passed=()
failed=()

for p in "${PRESETS[@]}"; do
  echo
  echo "=== $p ==="
  if cmake --workflow --preset "$p"; then passed+=("$p"); else failed+=("$p"); fi
done

echo
echo "=== Summary ==="
echo "PASS: ${passed[*]:-}"
echo "FAIL: ${failed[*]:-}"
exit "${#failed[@]}"
