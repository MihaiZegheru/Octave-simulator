#include "matrix.h"

int **read_matrix(unsigned int *size_i, unsigned int *size_j)
{
    scanf("%u%u", size_i, size_j);

    int **matrix = malloc(*size_i * sizeof(int*));

    for (unsigned int i = 0; i < *size_i; i++) {
        matrix[i] = malloc(*size_j * sizeof(int));
    }

    for (unsigned int i = 0; i < *size_i; i++) {
        for (int j = 0; j < *size_j; j++) {
            // scanf(%)
        }
    }
}