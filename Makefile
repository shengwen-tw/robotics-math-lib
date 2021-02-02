CC=gcc

CFLAGS=-g -O2

SRC=./src/matrix/matrix_standalone.c

CFLAGS+=-I./include/

OBJS=$(SRC:.c=.o)

build: $(OBJS)

%.o: %.c
	@echo "CC" $<
	@$(CC) $(CFLAGS) $^ -c -o $@
	
clean:
	rm -rf $(OBJS)

.PHONY: build clean
