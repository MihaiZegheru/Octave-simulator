CC=gcc
CFLAGS=-Wall -Wextra -std=c99
FILES=main.c matrix.c matrix_array.c io_utils.c app_manager.c

build:
	$(CC) $(CFLAG) $(FILES) -o my_octave
