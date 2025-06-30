# TODO:

CC = gcc
CFLAGS = -O3 -Wall --pedantic

BIN = bin
EXE = $(BIN)/naive \
	  $(BIN)/tiled

all: $(EXE)

run:
	sh -c 'for f in `ls $(BIN)` ; do echo "$$f:" ; $(BIN)/$$f ; echo "" ; done'

clean:
	rm bin/*

$(BIN)/naive: matvecmul.c algorithms/naive.h
	$(CC) $(CFLAGS) -o $@ -D MVM_NAIVE matvecmul.c

#$(BIN)/tiled-simple: matrix_transpose.c algorithms/tiled_simple.h 
#	$(CC) $(CFLAGS) -o $@ -D MT_TILED_SIMPLE matrix_transpose.c
#
$(BIN)/tiled: matvecmul.c algorithms/tiled.h 
	$(CC) $(CFLAGS) -o $@ -D MVM_TILED matvecmul.c

.PHONY: clean all
