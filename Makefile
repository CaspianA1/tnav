CC = gcc
CFLAGS = -lncurses -o main
RUN = ./main

all: build
	$(RUN)

build:
	$(CC) $(CFLAGS) -O3 main.c

# the -g flag is for gdb
debug:
	$(CC) $(CFLAGS) -g -O0 main.c

clean:
	rm -r *.dSYM
	rm *.out