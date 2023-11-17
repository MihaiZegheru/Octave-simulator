#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"
#include "io_utils.h"

void read_matrix_task(MatrixArray *matrix_array);
void print_matrix_task(MatrixArray *matrix_array);
void print_matrix_dimensions_task(MatrixArray *matrix_array);
void resize_matrix_task(MatrixArray *matrix_array);
void multiply_matrices_task(MatrixArray *matrix_array);
void strassen_multiply_matrices_task(MatrixArray *matrix_array);
void sort_matrix_array_task(MatrixArray *matrix_array);
void transpose_matrix_task(MatrixArray *matrix_array);
void pow_raise_matrix_task(MatrixArray *matrix_array);
void remove_matrix_task(MatrixArray *matrix_array);
void quit(MatrixArray *matrix_array);

#endif
