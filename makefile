CC=clang
FLAGS=-Wall -Wextra -std=c99 -ggdb

all: emulator.c
	$(CC) $(FLAGS) emulator.c -o out_em 

clean:
	rm out_em
