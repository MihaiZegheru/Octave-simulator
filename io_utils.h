#ifndef IO_UTILS_H__
#define IO_UTILS_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/**
 * @brief Reads a matrix_t and returns a matrix_t pointer.
 *
 * @return matrix_t*
 */
matrix_t *io_read_matrix();

/**
 * @brief Prints a matrix_t at the given address.
 *
 * @param matrix
 */
void io_print_matrix(matrix_t *matrix);

#endif
