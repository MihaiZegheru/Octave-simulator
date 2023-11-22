#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

#include "math_utils.h"

typedef struct {
	/**
	 * @brief The number of rows
	 */
	unsigned int size_n;
	/**
	 * @brief The number of columns
	 */
	unsigned int size_m;
	/**
	 * @brief The values in the matrix
	 */
	int **values;
} matrix_t;

/**
 * @brief Instantiates a new matrix_t in memory and returns the pointer.
 *
 * @param size_n
 * @param size_m
 * @return matrix_t*
 */
matrix_t *matrix_new(unsigned int size_n, unsigned int size_m);

/**
 * @brief Deletes the given matrix_t from memory.
 *
 * @param matrix
 */
void matrix_delete(matrix_t *matrix);

/**
 * @brief Resizes the given matrix_t including the intersection of the specified
 *        rows and columns.
 *
 * @param new_size_n
 * @param new_size_m
 * @param row_indexes array with row indexes to include
 * @param col_indexes array with column indexes to include
 * @param matrix
 */
void matrix_selective_resize(unsigned int new_size_n, unsigned int new_size_m,
			unsigned int *row_indexes, unsigned int *col_indexes,
			matrix_t *matrix);

/**
 * @brief Multiplies two given Matrices and returns the new one.
 *
 * @param matrix_a
 * @param matrix_b
 * @return matrix_t*
 */
matrix_t *matrix_multiply_matrices(matrix_t *matrix_a, matrix_t *matrix_b);

/**
 * @brief Multiplies two given Matrices using Strassen's algorithm and returns a
 *        new one.
 *
 * @param matrix_a
 * @param matrix_b
 * @return matrix_t*
 */
matrix_t *matrix_strassen_multiply_pot_matrices(matrix_t *matrix_a, matrix_t *matrix_b);

/**
 * @brief Transposes the given matrix_t and saves it at the same address.
 *
 * @param matrix
 */
void matrix_transpose(matrix_t *matrix);

/**
 * @brief Interface for raising the given matrix_t to a power in logarithmic time
 *        and saves it at the same address.
 *
 * @param power
 * @param matrix
 */
void matrix_power_raise(unsigned int power, matrix_t **matrix);

/**
 * @brief Swaps two Matrices.
 *
 * @param a
 * @param b
 */
void matrix_swap_matrices(matrix_t **a, matrix_t **b);

/**
 * @brief Resizes the given matrix_t, ignoring the old values.
 *
 * @param new_size_n
 * @param new_size_m
 * @param matrix
 */
void matrix_resize(unsigned int new_size_n, unsigned int new_size_m,
				   matrix_t *matrix);

/**
 * @brief Breaks the given matrix_t in 4 equal square blocks. Returns through
 *		  parameters.
 * @note The specified matrix must have equal sizes, powers of two.
 *
 * @param matrix
 * @param a returned block matrix address
 * @param b returned block matrix address
 * @param c returned block matrix address
 * @param d returned block matrix address
 */
void matrix_break_in_blocks(matrix_t *matrix, matrix_t **a, matrix_t **b, matrix_t **c,
							matrix_t **d);

/**
 * @brief Builds a matrix_t from 4 smaller blocks. Returns a new matrix_t.
 * @note The building blocks must all have equal sizes, powers of two.
 *
 * @param a
 * @param b
 * @param c
 * @param d
 * @return matrix_t*
 */
matrix_t *matrix_build_from_blocks(matrix_t *a, matrix_t *b, matrix_t *c, matrix_t *d);

/**
 * @brief The implementation of logarithmic power raising. Returns result matrix_t
 *		  as parameter.
 *
 * @param power
 * @param matrix
 * @param result_matrix
 */
void matrix_recursive_power_raise(unsigned int power, matrix_t *matrix,
								  matrix_t **result_matrix);

/**
 * @brief Calculates the sum of all the elements of the matrix.
 * @note The sum is modulo.
 *
 * @param *matrix:
 * @return int
 */
int matrix_compute_elements_sum(const matrix_t *matrix);

/**
 * @brief Calculates the difference between matrix_t a and matrix_t b;
 *        if a > b returns -1, else returns 0.
 * @note Used for sorting algorithms.
 *
 * @param a
 * @param b
 * @return int
 */
int matrix_cmp_matrices_ascending(const matrix_t *a, const matrix_t *b);

/**
 * @brief Calculates the difference between matrix_t b and matrix_t a;
 * @note Used for sorting algorithms.
 *
 * @param a
 * @param b
 * @return int
 */
int matrix_cmp_matrices_descending(const matrix_t *a, const matrix_t *b);

#endif
