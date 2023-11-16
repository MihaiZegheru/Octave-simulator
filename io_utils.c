#include "io_utils.h"

Matrix *read_matrix()
{
    // This does not check for mistakes in input
    unsigned int size_n, size_m;
    scanf("%u%u", &size_n, &size_m);

    Matrix *matrix = new_matrix(size_n, size_m);

    for (unsigned int i = 0; i < size_n; i++) {
        for (unsigned int j = 0; j < size_m; j++) {
            scanf("%d", &matrix->values[i][j]);
        }
    }

    return matrix;
}

void print_matrix(Matrix *matrix)
{
    for (unsigned int i = 0; i < matrix->size_n; i++) {
        for (unsigned int j = 0; j < matrix->size_m; j++) {
            printf("%d ", matrix->values[i][j]);
        }
        printf("\n");
    }
}