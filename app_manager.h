#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"
#include "io_utils.h"

/**
 * @brief Interface for reading a matrix from STDIN to a matrix_array_t.
 *
 * @param matrix_array
 */
void task_read_matrix(matrix_array_t *matrix_array);

/**
 * @brief Interface for printing a matrix from a matrix_array_t to STDOUT.
 *
 * @param matrix_array
 */
void task_print_matrix(matrix_array_t *matrix_array);

/**
 * @brief Interface for printing the dimensions of a matrix from a matrix_array_t.
 *
 * @param matrix_array
 */
void task_print_matrix_dimensions(matrix_array_t *matrix_array);

/**
 * @brief Interface for resizing a matrix from a matrix_array_t.
 *
 * @param matrix_array
 */
void task_resize_matrix(matrix_array_t *matrix_array);

/**
 * @brief Interface for multiplying matrices from a matrix_array_t.
 *
 * @param matrix_array
 */
void task_multiply_matrices(matrix_array_t *matrix_array);

/**
 * @brief Interface for multiplying matrices from a matrix_array_t using Strassen
 *        algorithm.
 *
 * @param matrix_array
 */
void task_strassen_multiply_matrices(matrix_array_t *matrix_array);

/**
 * @brief Interface for sorting a matrix_array_t.
 *
 * @param matrix_array
 */
void task_sort_matrix_array(matrix_array_t *matrix_array);

/**
 * @brief Interface for transposing a matrix from a matrix_array_t.
 *
 * @param matrix_array
 */
void task_transpose_matrix(matrix_array_t *matrix_array);

/**
 * @brief Interface for raising a matrix from a matrix_array_t to a power.
 *
 * @param matrix_array
 */
void task_pow_raise_matrix(matrix_array_t *matrix_array);

/**
 * @brief Interface for removing and DELETING a matrix from a matrix_array_t.
 *
 * @param matrix_array
 */
void task_remove_matrix(matrix_array_t *matrix_array);

/**
 * @brief Interface for quitting the program.
 *
 * @param matrix_array
 */
void task_quit(matrix_array_t *matrix_array);

#endif
