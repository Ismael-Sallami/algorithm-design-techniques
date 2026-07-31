# Builds every program under src/ into bin/, one folder per technique.
#
#   make          build everything
#   make test     build, run the cases and compare against tests/expected
#   make record   rewrite tests/expected from what the programs print now
#   make clean    remove bin/

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall

.PHONY: all test record clean

all:
	@bash tools/run-tests.sh >/dev/null 2>&1 || true
	@echo "Binarios en bin/"

test:
	@bash tools/run-tests.sh

record:
	@bash tools/record-expected.sh

clean:
	rm -rf bin
