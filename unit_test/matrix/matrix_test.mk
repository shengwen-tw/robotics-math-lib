CFLAGS=-g -O2
CFLAGS+=-I../../include

SRC=../../src/matrix/matrix_basic.c \
	../../src/matrix/matrix_util.c
SRC+=./main.c

build:
	gcc $(CFLAGS) -o matrix_test $(SRC)

clean:
	rm -rf matrix_test

.PHONY: build clean
