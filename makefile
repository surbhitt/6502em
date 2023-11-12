CC=clang
FLAGS=-Wall -Wextra -std=c99

all: emulator.c
	$(CC) emulator.c -o out_em $(FALGS)

clean:
	rm out_em
