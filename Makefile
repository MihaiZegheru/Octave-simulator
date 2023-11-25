#
#   Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
#   All rights reserved.
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99
FILES=main.c matrix.c m_math.c m_strassen.c matrix_array.c io_utils.c app_manager.c math_utils.c

build:
	$(CC) $(CFLAG) $(FILES) -o my_octave

clean:
	rm my_octave
