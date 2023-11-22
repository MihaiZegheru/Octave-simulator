#ifndef IO_UTILS_H__
#define IO_UTILS_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/**
 * @brief Reads a Matrix and returns a Matrix pointer.
 *
 * @return Matrix*
 */
Matrix *read_matrix();

/**
 * @brief Prints a Matrix at the given address.
 *
 * @param matrix
 */
void print_matrix(Matrix *matrix);

#endif
