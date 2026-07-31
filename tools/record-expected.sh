#!/usr/bin/env bash
# Records tests/expected/ from what the programs print right now.
#
# Run it only when a case is added or a program changes on purpose, and read the
# diff before committing: this is the file that decides what "correct" means.
#
#     bash tools/record-expected.sh
#
# @author Ismael Sallami Moreno
set -uo pipefail

cd "$(dirname "$0")/.." || exit 1
[ -d bin ] || { echo "Compila primero: bash tools/run-tests.sh"; exit 1; }

trabajo=$(mktemp -d)
trap 'rm -rf "$trabajo"' EXIT
mkdir -p tests/expected

while IFS='|' read -r caso binario args entrada; do
  caso=$(echo "$caso" | xargs)
  [ -z "$caso" ] && continue
  case "$caso" in \#*) continue ;; esac

  binario=$(echo "$binario" | xargs)
  args=$(echo "$args" | xargs)
  entrada=$(echo "$entrada" | xargs)

  [ -x "bin/$binario" ] || { echo "sin binario: $binario"; continue; }

  # shellcheck disable=SC2086  # $args tiene que partirse en argumentos sueltos
  ( cd "$trabajo" && printf '%s' "$entrada" | timeout 60 "$OLDPWD/bin/$binario" $args ) \
    > "tests/expected/$caso.txt" 2>/dev/null
  printf 'grabado  %-32s %s bytes\n' "$caso" "$(wc -c < "tests/expected/$caso.txt")"
done < tests/cases.txt
