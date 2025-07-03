
CC = gcc
CFLAGS = -O3 -Wall --pedantic

SRCS = matmatmul.c
BIN = bin
EXE = $(BIN)/naive \
	  $(BIN)/naive-loopswp # \
	  $(BIN)/tiled

all: $(EXE)

run:
	sh -c 'for f in `ls $(BIN)` ; do echo "$$f:" ; $(BIN)/$$f ; echo "" ; done'

clean:
	rm bin/*

$(BIN)/naive: $(SRCS) algorithms/naive.h
	$(CC) $(CFLAGS) -o $@ -D MMM_NAIVE $(SRCS)

$(BIN)/naive-loopswp: $(SRCS) algorithms/naive-loopswp.h
	$(CC) $(CFLAGS) -o $@ -D MMM_NAIVE_LOOPSWP $(SRCS)

#$(BIN)/tiled-simple: matrix_transpose.c algorithms/tiled_simple.h 
#	$(CC) $(CFLAGS) -o $@ -D MT_TILED_SIMPLE matrix_transpose.c
#
#$(BIN)/tiled: $(SRCS) algorithms/tiled.h 
#	$(CC) $(CFLAGS) -o $@ -D MMM_TILED $(SRCS)

.PHONY: clean all
