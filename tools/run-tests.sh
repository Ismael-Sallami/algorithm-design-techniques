#!/usr/bin/env bash
# Builds every program, runs the cases in tests/cases.txt and compares the output
# against tests/expected/. Then checks the thing these practices are actually
# about: that the iterative version and the divide-and-conquer version of the
# same problem agree.
#
# @author Ismael Sallami Moreno
set -uo pipefail

cd "$(dirname "$0")/.." || exit 1
BIN=bin
CXXFLAGS=(-std=c++17 -O2 -Wall)
fallos=0

titulo() { printf '\n── %s\n' "$1"; }
ok()     { printf '  ok    %s\n' "$1"; }
fallo()  { printf '  FALLO %s\n' "$1"; fallos=$((fallos + 1)); }

tecnica_de() {
  case "$1" in
    src/01-*) echo dnc ;;
    src/02-*) echo greedy ;;
    src/03-*) echo backtracking ;;
    src/04-*) echo dp ;;
  esac
}

# maze.cpp is a class that maze_backtracking.cpp includes, not a program.
es_cabecera() { [ "$(basename "$1")" = "maze.cpp" ]; }

falla_conocido() {
  grep -v '^\s*#' tools/known-build-failures.txt | grep -q "^$1\$"
}

# ── 1. Compilar ──────────────────────────────────────────────────────────────
titulo "compilando"
rm -rf "$BIN" && mkdir -p "$BIN"/{dnc,greedy,backtracking,dp}

while IFS= read -r fuente; do
  es_cabecera "$fuente" && continue
  destino="$BIN/$(tecnica_de "$fuente")/$(basename "$fuente" .cpp)"

  if g++ "${CXXFLAGS[@]}" -o "$destino" "$fuente" 2>/dev/null; then
    if falla_conocido "$fuente"; then
      fallo "$fuente compila, y esta declarado como fallo conocido. Actualiza la lista"
    else
      ok "$fuente"
    fi
  else
    if falla_conocido "$fuente"; then
      ok "$fuente no compila, como esta declarado"
    else
      fallo "$fuente no compila"
      g++ "${CXXFLAGS[@]}" -o /dev/null "$fuente" 2>&1 | head -3
    fi
  fi
done < <(find src -name '*.cpp' | sort)

# ── 2. Ejecutar los casos ────────────────────────────────────────────────────
titulo "ejecutando los casos"
trabajo=$(mktemp -d)
trap 'rm -rf "$trabajo"' EXIT

while IFS='|' read -r caso binario args entrada; do
  caso=$(echo "$caso" | xargs)
  [ -z "$caso" ] && continue
  case "$caso" in \#*) continue ;; esac

  binario=$(echo "$binario" | xargs)
  args=$(echo "$args" | xargs)
  entrada=$(echo "$entrada" | xargs)
  esperado="tests/expected/$caso.txt"

  if [ ! -x "$BIN/$binario" ]; then
    fallo "$caso: no existe $BIN/$binario"
    continue
  fi

  obtenido="$trabajo/$caso.txt"
  # En su propio directorio: alguno escribe ficheros al lado del ejecutable.
  # shellcheck disable=SC2086  # $args tiene que partirse en argumentos sueltos
  ( cd "$trabajo" && printf '%s' "$entrada" | timeout 60 "$OLDPWD/$BIN/$binario" $args ) \
    > "$obtenido" 2>/dev/null
  codigo=$?

  if grep -v '^\s*#' tools/known-crashes.txt | grep -q "^$caso\$"; then
    if [ "$codigo" -eq 0 ]; then
      fallo "$caso ya no revienta. Quitalo de tools/known-crashes.txt"
    else
      ok "$caso revienta, como esta declarado (codigo $codigo)"
    fi
    continue
  fi

  # Sin xargs: se comeria las barras invertidas del patron.
  patron=$(grep -v '^\s*#' tools/nondeterministic.txt | grep "^$caso *|" | cut -d'|' -f2- \
           | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//')
  if [ -n "$patron" ]; then
    if grep -qE "$patron" "$obtenido"; then
      ok "$caso cumple el patron esperado"
    else
      fallo "$caso: la salida no casa con $patron"
      head -5 "$obtenido"
    fi
    continue
  fi

  if [ ! -f "$esperado" ]; then
    fallo "$caso: falta tests/expected/$caso.txt"
    continue
  fi

  if diff -q "$esperado" "$obtenido" >/dev/null; then
    ok "$caso"
  else
    fallo "$caso: la salida no coincide"
    diff "$esperado" "$obtenido" | head -6
  fi
done < tests/cases.txt

# ── 3. Lo que va de estas practicas ──────────────────────────────────────────
titulo "las dos versiones del mismo problema coinciden"

comparar() {
  if diff -q "tests/expected/$1.txt" "tests/expected/$2.txt" >/dev/null; then
    ok "$3"
  else
    fallo "$3: $1 y $2 dan resultados distintos"
  fi
}

comparar absolute_majority_iterative     absolute_majority_divide     "mayoria absoluta, con mayoria"
comparar absolute_majority_iterative_tie absolute_majority_divide_tie "mayoria absoluta, sin mayoria"
comparar tournament_calendar_iterative   tournament_calendar_divide   "calendario del campeonato"

# El producto de tres imprime que tecnica ha usado, asi que se compara el
# veredicto y no la linea entera.
veredicto() { grep -o 'Verdad\|Falso' "tests/expected/$1.txt" | head -1; }
for par in "product_of_three_iterative product_of_three_divide 120" \
           "product_of_three_iterative_no product_of_three_divide_no 121"; do
  # shellcheck disable=SC2086  # aqui la particion en palabras es el objetivo
  set -- $par
  if [ "$(veredicto "$1")" = "$(veredicto "$2")" ]; then
    ok "producto de tres consecutivos, n=$3"
  else
    fallo "producto de tres consecutivos, n=$3: veredictos distintos"
  fi
done

# Eliminar repetidos es el caso interesante: la version divide y venceras
# devuelve el mismo conjunto pero ordenado, porque el orden le sale gratis al
# mezclar. Se comparan como conjuntos, que es lo que el problema pide.
conjunto() { tr ' ' '\n' < "tests/expected/$1.txt" | grep -E '^[0-9]+$' | sort -n | uniq; }
if diff -q <(conjunto remove_duplicates_iterative) <(conjunto remove_duplicates_divide) >/dev/null; then
  ok "eliminar repetidos, mismo conjunto en las dos versiones"
else
  fallo "eliminar repetidos: las dos versiones no dejan el mismo conjunto"
fi

echo
if [ "$fallos" -eq 0 ]; then
  echo "Todo correcto."
else
  echo "$fallos comprobaciones han fallado."
  exit 1
fi
