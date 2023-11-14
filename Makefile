CC=gcc
CFLAGS=-Wall -Wextra -std=c99
FILES=main.c matrix.c matrix_array.c

build:
	$(CC) $(CFLAG) $(FILES) -o main
