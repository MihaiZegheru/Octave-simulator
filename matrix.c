#include "matrix.h"

Matrix *new_matrix(unsigned int size_n, unsigned int size_m) {
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