#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix read_matrix()
{
    // This does not check for mistakes in input
    unsigned int size_n, size_m;
    scanf("%u%u", &size_n, &size_m);

    Matrix matrix;
    *matrix.values = malloc(size_n * sizeof(int*));
    if (*matrix.values == NULL) {
        // err
    }

    for (unsigned int i = 0; i < size_n; i++) {
        matrix.values[i] = malloc(size_m * sizeof(int));
        if (matrix.values[i] == NULL) {
            // err
        }
    }

    for (int i = 0; i < size_n; i++) {
        for (int j = 0; j < size_m; j++) {
            scanf("%d", matrix.values[i][j]);
        }
    }

    return matrix;
}

void print_matrix(Matrix matrix)
{
    for (int i = 0; i < matrix.size_n; i++) {
        for (int j = 0; j < matrix.size_m; j++) {
            printf("%d ", matrix.values[i][j]);
        }
        printf("\n");
    }
}
