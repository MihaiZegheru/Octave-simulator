#include "matrix.h"

#include "io_utils.h" // TO BE DELETED

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

void transpose_matrix(Matrix *matrix)
{
    unsigned int new_size_n = matrix->size_m;
    unsigned int new_size_m = matrix->size_n;

    Matrix *aux_matrix = new_matrix(new_size_n, new_size_m);

    printf("A");

    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            aux_matrix->values[i][j] = matrix->values[j][i];
        }
    }
printf("A");
    resize_matrix(new_size_n, new_size_m, matrix);
printf("A");
printf("%d %d ", sizeof(matrix->values), sizeof(matrix->values[0]));
    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            matrix->values[i][j] = aux_matrix->values[i][j];
            printf("%d ", matrix->values[i][j]);
        }
        printf("\n");
    }
    printf("A");

    delete_matrix(aux_matrix);
}

void recursive_power_raise_matrix(unsigned int power, Matrix *matrix, Matrix **result_matrix)
{
    if (power == 0) {
        for (unsigned int i = 0; i < matrix->size_n; i++) {
            for (unsigned int j = 0; j < matrix->size_m; j++) {
                if (i == j) {
                    (*result_matrix)->values[i][j] = 1;
                }
                else {
                    (*result_matrix)->values[i][j] = 0;
                }
            }
        }

        return;
    }

    if (power % 2) {
        recursive_power_raise_matrix(power - 1, matrix, result_matrix);
        Matrix *new_matrix = multiply_matrices(matrix, *result_matrix);

        delete_matrix(*result_matrix);
        *result_matrix = new_matrix;
    }
    else {
        recursive_power_raise_matrix(power / 2, matrix, result_matrix);
        Matrix *new_matrix = multiply_matrices(*result_matrix, *result_matrix);

        delete_matrix(*result_matrix);
        *result_matrix = new_matrix;
    }
}

void power_raise_matrix(unsigned int power, Matrix **matrix)
{
    Matrix *result_matrix = new_matrix((*matrix)->size_n, (*matrix)->size_m);
    recursive_power_raise_matrix(power, *matrix, &result_matrix);

    delete_matrix(*matrix);
    *matrix = result_matrix;
        print_matrix(*matrix);
}

void swap_matrix_pointers(Matrix **a, Matrix **b)
{
    Matrix *aux = *a;
    *a = *b;
    *b = aux;
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
            matrix->values[i] = malloc(new_size_m * sizeof(int));

            if (matrix->values[i] == NULL) {
                // err
            }
        }
    }
}

int compute_elements_sum(const Matrix *matrix)
{
    int sum = 0;

    for (unsigned int i = 0; i < matrix->size_n; i++) {
        for (unsigned int j = 0; j < matrix->size_m; j++) {
            sum += matrix->values[i][j]; // TODO: add modulo
        }
    }

    return sum;
}

short int cmp_matrices_ascending(const Matrix *a, const Matrix *b)
{
    int sum_a = compute_elements_sum(a);
    int sum_b = compute_elements_sum(b);

    if (sum_a < sum_b) {
        return 1;
    }
    else if (sum_a > sum_b) {
        return -1;
    }
    
    return 0;
}

short int cmp_matrices_descending(const Matrix *a, const Matrix *b)
{
    int sum_a = compute_elements_sum(a);
    int sum_b = compute_elements_sum(b);

    if (sum_a > sum_b) {
        return 1;
    }
    else if (sum_a < sum_b) {
        return -1;
    }

    return 0;
}