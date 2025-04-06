# TODO:

CC = gcc
CFLAGS = -O3 -Wall --pedantic

BIN = bin
EXE = $(BIN)/naive \
	  $(BIN)/naive-swapped-loops \
	  $(BIN)/tiled-simple \
	  $(BIN)/tiled-generic

all: $(EXE)

run:
	sh -c 'for f in `ls $(BIN)` ; do echo "$$f:" ; $(BIN)/$$f ; echo "" ; done'

clean:
	rm bin/*

$(BIN)/naive: matrix_transpose.c algorithms/naive.h
	$(CC) $(CFLAGS) -o $@ -D MT_NAIVE matrix_transpose.c

$(BIN)/naive-swapped-loops: matrix_transpose.c algorithms/naive_swapped_loops.h 
	$(CC) $(CFLAGS) -o $@ -D MT_NAIVE_LOOPSWAP matrix_transpose.c

$(BIN)/tiled-simple: matrix_transpose.c algorithms/tiled_simple.h 
	$(CC) $(CFLAGS) -o $@ -D MT_TILED_SIMPLE matrix_transpose.c

$(BIN)/tiled-generic: matrix_transpose.c algorithms/tiled_generic.h 
	$(CC) $(CFLAGS) -o $@ -D MT_TILED_GENERIC matrix_transpose.c

.PHONY: clean all
