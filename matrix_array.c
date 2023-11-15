#include "matrix_array.h"

#include "io_handle.h"

MatrixArray *new_matrix_array(unsigned int starting_capacity)
{
    MatrixArray *matrix_array = malloc(sizeof(MatrixArray));

    matrix_array->matrices = malloc(starting_capacity * sizeof(Matrix *)); 
    if (matrix_array->matrices == NULL && starting_capacity) {
        // err
    }

    matrix_array->capacity = starting_capacity;
    matrix_array->size = 0;

    return matrix_array;
}

void delete_matrix_array(MatrixArray *matrix_array)
{
    free(matrix_array->matrices);
    free(matrix_array);
}

void add_matrix(MatrixArray *matrix_array)
{
    if (matrix_array->size + 1 >= matrix_array->capacity) {
        double_matrix_array_capacity(matrix_array);
    }

    Matrix matrix = read_matrix();
    matrix_array->matrices[matrix_array->size] = matrix;
    matrix_array->size++;
}

void double_matrix_array_capacity(MatrixArray *matrix_array)
{
    matrix_array->capacity *= 2;
    matrix_array->matrices = realloc(matrix_array->matrices,
                                     matrix_array->capacity * sizeof(int*));

    if (matrix_array->matrices == NULL) {
        // err
    }
}
