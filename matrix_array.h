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

void add_matrix(Matrix *matrix, MatrixArray *matrix_array);
void remove_matrix(unsigned int index, MatrixArray *matrix_array);
Matrix *get_matrix_by_value(unsigned int index, MatrixArray *matrix_array);
Matrix **get_matrix_by_reference(unsigned int index, MatrixArray *matrix_array);

Matrix **quick_sort_partition(Matrix **pivot, Matrix **first, Matrix **last, short int (*cmp)(const Matrix *, const Matrix *));
void quick_sort(Matrix **first, Matrix **last, short int (*cmp)(const Matrix *, const Matrix *));

void double_matrix_array_capacity(MatrixArray *matrix_array);
void half_matrix_array_capacity(MatrixArray *matrix_array);

#endif
