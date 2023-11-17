#include "matrix.h"

#include "io_utils.h" // TO BE DELETED

#define MODULO 10007

Matrix *new_matrix(unsigned int size_n, unsigned int size_m)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->size_n = size_n;
    matrix->size_m = size_m;

    matrix->values = malloc(size_n * sizeof(int*));
    if (matrix->values == NULL) {
        // err
        printf("ERR");
    }

    for (unsigned int i = 0; i < size_n; i++) {
        matrix->values[i] = malloc(size_m * sizeof(int));
        if (matrix->values[i] == NULL) {
            // err
            printf("ERR");
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
    printf("AA");
    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            unsigned int index_i = row_indexes[i];
            unsigned int index_j = col_indexes[j];

            aux_matrix->values[i][j] = matrix->values[index_i][index_j];
        }
    }
    printf("AA");
    resize_matrix(new_size_n, new_size_m, matrix);
    printf("AA");
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
                sum = modulo(sum + matrix_a->values[i][k] * matrix_b->values[k][j]);
            }

            result->values[i][j] = sum;
        }
    }

    return result;
}

void break_matrix_in_blocks(Matrix *matrix, Matrix *a, Matrix *b, Matrix *c, Matrix *d)
{
    unsigned int new_size_n = matrix->size_n / 2;
    unsigned int new_size_m = matrix->size_m / 2;

    a = new_matrix(new_size_n, new_size_m);
    b = new_matrix(new_size_n, new_size_m);
    c = new_matrix(new_size_n, new_size_m);
    d = new_matrix(new_size_n, new_size_m);

    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            a->values[i][j] = matrix->values[i][j];
            b->values[i][j] = matrix->values[i][new_size_m + j];
            c->values[i][j] = matrix->values[new_size_n + i][j];
            d->values[i][j] = matrix->values[new_size_n + i][new_size_m + j];
        }
    }
}

Matrix *make_matrix_from_blocks(Matrix *a, Matrix *b, Matrix *c, Matrix *d)
{
    unsigned int new_size_n = a->size_n + c->size_n;
    unsigned int new_size_m = a->size_m + b->size_m;

    Matrix *matrix = new_matrix(new_size_n, new_size_m);

    for (unsigned int i = 0; i < a->size_n; i++) {
        for (unsigned int j = 0; j < a->size_m; j++) {
            matrix->values[i][j] = a->values[i][j];
            matrix->values[i][a->size_m + j] = b->values[i][j];
            matrix->values[a->size_n + i][j] = c->values[i][j];
            matrix->values[a->size_n + i][a->size_m + j] = d->values[i][j];
        }
    }

    return matrix;
}

Matrix *strassen_multiply_matrices(Matrix *matrix_a, Matrix *matrix_b)
{
    // This implemntation works on matrices that have a size of 2^n
    if (matrix_a->size_n == 1) {
        return;
    }

    Matrix *a_1, *a_2, *a_3, *a_4;
    break_matrix_in_blocks(matrix_a, a_1, a_2, a_3, a_4);

    Matrix *b_1, *b_2, *b_3, *b_4;
    break_matrix_in_blocks(matrix_a, a_1, a_2, a_3, a_4);

    Matrix *add_a_1_a_4 = add_matrices(a_1, a_4);
    Matrix *add_b_1_b_4 = add_matrices(b_1, b_4);
    Matrix *m_1 = strassen_multiply_matrices(add_a_1_a_4, add_b_1_b_4);
    delete_matrix(add_b_1_b_4);
    delete_matrix(add_a_1_a_4);

    Matrix *add_a_3_a_4 = add_matrices(a_1, a_4);
    Matrix *m_2 = strassen_multiply_matrices(add_a_3_a_4, b_1);
    delete_matrix(add_a_3_a_4);

    Matrix *sub_b_2_b_4 = subtract_matrices(b_2, b_4);
    Matrix *m_3 = strassen_multiply_matrices(a_1, sub_b_2_b_4);
    delete_matrix(sub_b_2_b_4);

    Matrix *sub_b_3_b_1 = subtract_matrices(b_3, b_1);
    Matrix *m_4 = strassen_multiply_matrices(a_4, sub_b_3_b_1);
    delete_matrix(sub_b_3_b_1);

    Matrix *add_a_1_a_2 = add_matrices(a_1, a_2);
    Matrix *m_5 = strassen_multiply_matrices(add_a_1_a_2, b_4);
    delete_matrix(add_a_1_a_2);

    Matrix *sub_a_3_a_1 = subtract_matrices(a_3, a_1);
    Matrix *add_b_1_b_2 = add_matrices(b_1, b_2);
    Matrix *m_6 = strassen_multiply_matrices(sub_a_3_a_1, add_b_1_b_2);
    delete_matrix(add_b_1_b_2);
    delete_matrix(sub_a_3_a_1);

    Matrix *sub_a_2_a_4 = subtract_matrices(a_2, a_4);
    Matrix *add_b_3_b_4 = add_matrices(b_3, b_4);
    Matrix *m_7 = strassen_multiply_matrices(sub_a_2_a_4, add_b_3_b_4);
    delete_matrix(add_b_3_b_4);
    delete_matrix(sub_a_2_a_4);
}

void transpose_matrix(Matrix *matrix)
{
    unsigned int new_size_n = matrix->size_m;
    unsigned int new_size_m = matrix->size_n;

    Matrix *aux_matrix = new_matrix(new_size_n, new_size_m);

    for (unsigned int i = 0; i < new_size_n; i++) {
        for (unsigned int j = 0; j < new_size_m; j++) {
            aux_matrix->values[i][j] = matrix->values[j][i];
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

Matrix *add_matrices(Matrix *a, Matrix *b)
{
    if (a->size_n != b->size_n || a->size_m != b->size_m) {
        return NULL;
    }

    Matrix *matrix = new_matrix(a->size_n, a->size_m);
    for (unsigned int i = 0; i < a->size_n; i++) {
        for (unsigned int j = 0; j < a->size_m; j++) {
            matrix->values[i][j] = modulo(a->values[i][j] + b->values[i][j]);
        }
    }

    return matrix;
}

Matrix *subtract_matrices(Matrix *a, Matrix *b)
{
    if (a->size_n != b->size_n || a->size_m != b->size_m) {
        return NULL;
    }

    Matrix *matrix = new_matrix(a->size_n, a->size_m);
    for (unsigned int i = 0; i < a->size_n; i++) {
        for (unsigned int j = 0; j < a->size_m; j++) {
            matrix->values[i][j] = modulo(a->values[i][j] - b->values[i][j]);
        }
    }

    return matrix;
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
            sum = modulo(sum + matrix->values[i][j]);
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

int modulo(int value)
{
    value %= MODULO;

    if (value < 0) {
        return value + MODULO;
    }

    return value;
}