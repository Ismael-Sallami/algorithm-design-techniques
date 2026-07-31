# algorithm-design-techniques

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
[![tests](https://img.shields.io/github/actions/workflow/status/Ismael-Sallami/algorithm-design-techniques/ci.yml?branch=main&logo=github&label=tests)](https://github.com/Ismael-Sallami/algorithm-design-techniques/actions/workflows/ci.yml)
![license](https://img.shields.io/badge/license-MIT-4c1)

Nineteen problems solved with the four classic algorithm design techniques, in C++: divide
and conquer, greedy, backtracking with branch and bound, and dynamic programming.

## Context

Coursework for **Algorítmica**, year 2 of the double degree in Computer Science and Business
Administration, University of Granada (2023-24). Team work with **José Ángel Carretero
Montes**, **Fernando José Gracia Choin**, **Minerva Cebrián Marín** and **Jesús Rodríguez
González**.

It was handed in as four separate repositories, one per practical, and this is the four
brought together. **Practical 1 is not here**: it was the empirical efficiency study and no
copy of it survives in any of our accounts. The numbering below follows the course, so it
starts at two.

## The problem

The subject is not about the problems. It is about the technique: the same statement is
handed to you twice, in two different practicals, so that you have to solve it once with a
greedy algorithm and once with backtracking and see for yourself where the first one gives
up.

Student pairing and the circular table appear in both practical 3 and practical 4 for that
reason, and the pair is the most interesting thing in this repository. The greedy version
takes the best available pair at each step and finishes instantly; backtracking explores and
finds an optimum the greedy one misses, and pays for it.

Divide and conquer adds a second question on top: past what size is splitting worth it?
Every problem in practical 2 comes in three versions — iterative, recursive, and a hybrid
that switches to the iterative one below a threshold — plus the benchmark that measures where
that threshold is.

## The solution

**Practical 2 — divide and conquer.** Absolute majority in a vote count, matching nuts to
bolts without ever comparing two nuts, deciding whether a number is the product of three
consecutive naturals, removing duplicates, and building a round-robin calendar by doubling a
half-sized one. Five problems, each in its three versions.

**Practical 3 — greedy.** Pairing students, seating guests at a circular table, choosing
refuelling stops to make as few as possible, routing sensor data with Dijkstra, and paving
the streets of a village with a minimum spanning tree.

**Practical 4 — backtracking and branch and bound.** The first two problems again, plus
peg solitaire on a 7×7 board, a maze solved by backtracking, and the same maze solved with a
bound so that the path found is the shortest.

**Practical 5 — dynamic programming.** The cheapest downstream trip on a river, minimum
flight times with stopovers by Floyd, the most gold collectable crossing a grid, and the
cheapest descent of a mountain. All four fill a table and then walk it backwards to recover
the route, which is the half people skip.

## Layout

```
src/01-divide-and-conquer/    five problems, three versions each, plus the benchmarks
src/02-greedy/                five problems
src/03-backtracking-and-branch-and-bound/   five problems, sharing maze.cpp
src/04-dynamic-programming/   four problems
tests/cases.txt               arguments and stdin for each case
tests/expected/               the output each one has to produce
tools/run-tests.sh            builds, runs and compares
tools/known-build-failures.txt, known-crashes.txt, nondeterministic.txt
```

## Requirements

- A C++17 compiler. Tested with g++ 13 and 14
- `make`, optional: everything runs through `bash tools/run-tests.sh`
- `graphviz`, only if you want `street_paving` to draw its graph

## Build and run

```bash
git clone https://github.com/Ismael-Sallami/algorithm-design-techniques.git
cd algorithm-design-techniques

make test          # builds everything, runs the cases, compares the output
```

Individual programs, once built:

```bash
./bin/dnc/absolute_majority_divide 7 1 1 2 1 3 1 1
./bin/greedy/bus_refuelling
./bin/backtracking/senku
./bin/dp/gold_grid
```

The benchmarks are the exception. They sweep sizes from 10,000 to 100,000 writing timings to
a file, and take minutes:

```bash
./bin/dnc/absolute_majority_threshold_benchmark output.dat 42 0 100
```

## Results

`make test` builds 31 programs and runs 27 cases. Dynamic programming on the grid of gold,
for instance:

```
Matriz T:
0	1	1	-∞	0
0	-∞	2	2	2
0	0	-∞	2	3
1	1	1	3	3
Máximo oro recogido: 3
Ruta: (0,0) (0,1) (1,2) (1,3) (2,4) (3,4)
```

And the check that matters in practical 2, which is that the two ways of solving the same
problem agree:

```
── las dos versiones del mismo problema coinciden
  ok    mayoria absoluta, con mayoria
  ok    mayoria absoluta, sin mayoria
  ok    calendario del campeonato
  ok    producto de tres consecutivos, n=120
  ok    producto de tres consecutivos, n=121
  ok    eliminar repetidos, mismo conjunto en las dos versiones
```

The last line is not the same check as the others. Removing duplicates by divide and conquer
returns **the same set in a different order**, because sorting falls out of the merge for
free, so what is compared there is the set and not the text.

## What I learned

- Solving the same statement twice, once greedily and once with backtracking, teaches more
  than either alone. The greedy pairing is not wrong so much as satisfied too early.
- A hybrid with a threshold is the honest answer to "which is faster". Recursion wins
  asymptotically and loses on small inputs, and the crossover is a number you measure rather
  than a matter of opinion.
- Every dynamic programming problem here is two halves: filling the table, which is
  mechanical, and walking it back to recover the route, which is where the mistakes are.
- **Limitations, and the two defects left as they were handed in:**
  - **`nuts_and_bolts_iterative` segfaults on every run.** Its counting sort loops with
    `for (size_t i = arr1.size() - 1; i >= 0; --i)`, and `i >= 0` is always true for an
    unsigned type, so after zero it wraps around and reads out of bounds. The second half of
    the same function loops with `int` and is fine, which is what makes it look right.
    Asserted in `tools/known-crashes.txt`.
  - **`river_trip` does not compile.** It uses `INT32_MAX` without including `<cstdint>`;
    GCC used to provide it through another header and no longer does, so what was marked in
    2024 does not build today. Asserted in `tools/known-build-failures.txt`.
  - Neither is fixed. A submission rewritten to please a compiler is not the submission any
    more, so both are asserted instead: if either ever starts working, the tests fail and the
    list gets corrected rather than quietly lying.
  - `greedy/student_pairing` seeds with `time(NULL)`, so it cannot have a fixed expected
    output. What the test checks there is the shape of the answer, declared in
    `tools/nondeterministic.txt`.
  - The code, the comments and the program output are in Spanish.

## Authors and licence

José Ángel Carretero Montes, Ismael Sallami Moreno, Fernando José Gracia Choin, Minerva
Cebrián Marín and Jesús Rodríguez González. Released under the MIT licence (see `LICENSE`).
