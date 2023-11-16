#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"
#include "io_utils.h"

void read_matrix_task(MatrixArray *matrix_array)
{
    Matrix *matrix = read_matrix();
    add_matrix(matrix, matrix_array);
}

void print_matrix_task(MatrixArray *matrix_array)
{
    unsigned int index;
    scanf("%u", &index);

    Matrix *matrix = get_matrix_by_index(index, matrix_array);
    if (matrix == NULL) {
        printf("No matrix with the given index\n");
        return;
    }
    print_matrix(matrix);
}

void print_matrix_dimensions_task(MatrixArray *matrix_array)
{
    unsigned int index;
    scanf("%u", &index);

    Matrix *matrix = get_matrix_by_index(index, matrix_array);
    if (matrix == NULL) {
        printf("No matrix with the given index\n");
        return;
    }
    printf("%u %u\n", matrix->size_n, matrix->size_m);
}

void resize_matrix_task(MatrixArray *matrix_array)
{
    unsigned int index;
    scanf("%u", &index);

    unsigned int new_size_n;
    scanf("%u", &new_size_n);

    unsigned int *row_indexes = malloc(new_size_n * sizeof(int));
    if (row_indexes == NULL) {
        // err
    }

    for (unsigned int i = 0 ; i < new_size_n; i++) {
        scanf("%u", &row_indexes[i]);
        row_indexes[i]--;
    }

    unsigned int new_size_m;
    scanf("%u", &new_size_m);

    unsigned int *col_indexes = malloc(new_size_m * sizeof(int));
    if (col_indexes == NULL) {
        // err
    }

    for (unsigned int i = 0 ; i < new_size_m; i++) {
        scanf("%u", &col_indexes[i]);
        col_indexes[i]--;
    }

    Matrix *matrix = get_matrix_by_index(index, matrix_array);
    if (matrix == NULL) {
        printf("No matrix with the given index\n");

        free(row_indexes);
        free(col_indexes);
        return;
    }
    
    resize(new_size_n, new_size_m, row_indexes, col_indexes, matrix);

    free(row_indexes);
    free(col_indexes);
}

#endif
