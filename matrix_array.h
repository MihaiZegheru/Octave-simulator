#ifndef MATRIX_ARRAY_H__
#define MATRIX_ARRAY_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

typedef struct {
    unsigned int capacity;
    unsigned int size;
    Matrix **matrices;
} MatrixArray;

MatrixArray *new_matrix_array(unsigned int starting_capacity);
void delete_matrix_array(MatrixArray *matrix_array);

Matrix *add_matrix(MatrixArray *matrix_array);
Matrix *get_matrix_by_index(unsigned int index, MatrixArray *matrix_array);

void double_matrix_array_capacity(MatrixArray *matrix_array);

#endif
