#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"
#include "io_utils.h"

/**
 * @brief Interface for reading a matrix from STDIN to a MatrixArray.
 *
 * @param matrix_array
 */
void read_matrix_task(MatrixArray *matrix_array);

/**
 * @brief Interface for printing a matrix from a MatrixArray to STDOUT.
 *
 * @param matrix_array
 */
void print_matrix_task(MatrixArray *matrix_array);

/**
 * @brief Interface for printing the dimensions of a matrix from a MatrixArray.
 *
 * @param matrix_array
 */
void print_matrix_dimensions_task(MatrixArray *matrix_array);

/**
 * @brief Interface for resizing a matrix from a MatrixArray.
 *
 * @param matrix_array
 */
void resize_matrix_task(MatrixArray *matrix_array);

/**
 * @brief Interface for multiplying matrices from a MatrixArray.
 *
 * @param matrix_array
 */
void multiply_matrices_task(MatrixArray *matrix_array);

/**
 * @brief Interface for multiplying matrices from a MatrixArray using Strassen
 *        algorithm.
 *
 * @param matrix_array
 */
void strassen_multiply_matrices_task(MatrixArray *matrix_array);

/**
 * @brief Interface for sorting a MatrixArray.
 *
 * @param matrix_array
 */
void sort_matrix_array_task(MatrixArray *matrix_array);

/**
 * @brief Interface for transposing a matrix from a MatrixArray.
 *
 * @param matrix_array
 */
void transpose_matrix_task(MatrixArray *matrix_array);

/**
 * @brief Interface for raising a matrix from a MatrixArray to a power.
 *
 * @param matrix_array
 */
void pow_raise_matrix_task(MatrixArray *matrix_array);

/**
 * @brief Interface for removing and DELETING a matrix from a MatrixArray.
 *
 * @param matrix_array
 */
void remove_matrix_task(MatrixArray *matrix_array);

/**
 * @brief Interface for quitting the program.
 *
 * @param matrix_array
 */
void quit(MatrixArray *matrix_array);

#endif
