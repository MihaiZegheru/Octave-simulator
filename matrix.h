#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int size_n, size_m;
    int **values;
} Matrix;

Matrix *new_matrix(unsigned int size_n, unsigned int size_m);
Matrix *new_matrix();

#endif
