CC=clang
FLAGS=-Wall -Wextra -std=c99 -ggdb

all: main.c
	$(CC) main.c -o out_em 
	# ./out_em
	
eg: all
	./out_em eg1.asm

clean:
	rm out_em
