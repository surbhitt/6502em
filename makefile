CC=clang
FLAGS=-Wall -Wextra -std=c99 -ggdb

EXAMPLES_DIR=examples/

all: main.c
	$(CC) main.c -o out_em 
	
eg1: all
	./out_em $(EXAMPLES_DIR)1-3pixels.asm

eg2: all
	./out_em $(EXAMPLES_DIR)2-tax.asm

clean:
	rm out_em
