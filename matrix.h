#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int size_n, size_m;
    int **values;
} Matrix;

Matrix *new_matrix(unsigned int size_n, unsigned int size_m);
void delete_matrix(Matrix *matrix);

void resize(unsigned int new_size_n, unsigned int new_size_m, unsigned int *row_indexes, unsigned int *col_indexes, Matrix *matrix);

void resize_matrix(unsigned int new_size_n, unsigned int new_size_m, Matrix *matrix);

#endif
