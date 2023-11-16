#include "matrix.h"

Matrix *new_matrix(unsigned int size_n, unsigned int size_m)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->size_n = size_n;
    matrix->size_m = size_m;

    matrix->values = malloc(size_n * sizeof(int*));
    if (matrix->values == NULL) {
        // err
    }

    for (unsigned int i = 0; i < size_n; i++) {
        matrix->values[i] = malloc(size_m * sizeof(int));
        if (matrix->values[i] == NULL) {
            // err
        }
    }

    return matrix;
}

void delete_matrix(Matrix *matrix)
{
    for (unsigned int i = 0; i < matrix->size_n; i++) {
        free(matrix->values[i]);
    }

    free(matrix->values);
    free(matrix);
}

void resize(unsigned int new_size_n, unsigned int new_size_m, unsigned int *row_indexes, unsigned int *col_indexes, Matrix *matrix)
{
    Matrix *aux_matrix = new_matrix(new_size_n, new_size_m);

    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            unsigned int index_i = row_indexes[i];
            unsigned int index_j = col_indexes[j];

            aux_matrix->values[i][j] = matrix->values[index_i][index_j];
        }
    }

    resize_matrix(new_size_n, new_size_m, matrix);

    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            matrix->values[i][j] = aux_matrix->values[i][j];
        }
    }

    delete_matrix(aux_matrix);
}

Matrix *multiply_matrices(Matrix *matrix_a, Matrix *matrix_b)
{
    if (matrix_a->size_m != matrix_b->size_n) {
        return NULL;
    }

    unsigned int common_size = matrix_a->size_m;
    unsigned int new_size_n = matrix_a->size_n;
    unsigned int new_size_m = matrix_b->size_m;

    Matrix *result = new_matrix(new_size_n, new_size_m);

    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            int sum = 0;
            for (unsigned int k = 0; k < common_size; k++) {
                sum += matrix_a->values[i][k] * matrix_b->values[k][j]; // TODO: add modulo
            }

            result->values[i][j] = sum;
        }
    }

    return result;
}

void resize_matrix(unsigned int new_size_n, unsigned int new_size_m, Matrix *matrix)
{
    matrix->size_n = new_size_n;
    matrix->size_m = new_size_m;

    matrix->values = realloc(matrix->values, new_size_n * sizeof(int*));
    if (matrix->values == NULL) {
        // err
    }

    for (unsigned int i = 0; i < new_size_n; i++) {
        matrix->values[i] = realloc(matrix->values[i], new_size_m * sizeof(int));
        if (matrix->values[i] == NULL) {
            // err
        }
    }
}