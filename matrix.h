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
Matrix *multiply_matrices(Matrix *matrix_a, Matrix *matrix_b);
void transpose_matrix(Matrix *matrix);
void power_raise_matrix(unsigned int power, Matrix **matrix);

void swap_matrix_pointers(Matrix **a, Matrix **b);
void resize_matrix(unsigned int new_size_n, unsigned int new_size_m, Matrix *matrix);
void recursive_power_raise_matrix(unsigned int power, Matrix *matrix, Matrix **result_matrix);
short int cmp_matrices_ascending(const Matrix *a, const Matrix *b);
short int cmp_matrices_descending(const Matrix *a, const Matrix *b);

#endif
