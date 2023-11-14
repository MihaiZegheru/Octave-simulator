#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **matrix;
} Matrix;

int **read_matrix(unsigned int *size_i, unsigned int *size_j);

#endif
