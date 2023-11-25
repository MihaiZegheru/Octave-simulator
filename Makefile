#
#   Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
#   All rights reserved.
#

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SOURCES=main.c 			\
		matrix.c 		\
		m_math.c 		\
		m_strassen.c 	\
		matrix_array.c 	\
		io_utils.c 		\
		app_manager.c 	\
		math_utils.c

HEADERS=matrix.h 		\
		matrix_array.h 	\
		io_utils.h 		\
		app_manager.h 	\
		math_utils.h

EXTRAS=Makefile README

build:
	$(CC) $(CFLAG) $(SOURCES) -o my_octave

pack:
	zip -FSr 312CA_ZegheruMihai_Tema2.zip $(SOURCES) $(HEADERS) $(EXTRAS)

clean:
	rm my_octave
