#ifndef MATRIX_ARRAY_H__
#define MATRIX_ARRAY_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

typedef struct {
	/**
	 * @brief The number of elements the array has currently allocated
	 *        space for.
	 */
	unsigned int capacity;
	/**
	 * @brief The number of elements in the array.
	 */
	unsigned int size;
	/**
	 * @brief The array of pointers of the Matrices in the array.
	 */
	matrix_t **matrices;
} matrix_array_t;

/**
 * @brief Instantiates a new matrix_array_t in memory and returns the pointer.
 * @note Can be instantiated with 0 capacity.
 *
 * @param starting_capacity
 * @return matrix_array_t*
 */
matrix_array_t *matrix_array_new(unsigned int starting_capacity);
/**
 * @brief Deletes the given matrix_array_t from memory.
 *
 * @param matrix_array
 */

void matrix_array_delete(matrix_array_t *matrix_array);

/**
 * @brief Adds the given matrix_t to the array as a pointer.
 * @note Adding the same matrix twice will result in two positions in the
 *       array pointing to the same matrix.
 *
 * @param matrix
 * @param matrix_array
 */
void matrix_array_add_matrix(matrix_t *matrix, matrix_array_t *matrix_array);

/**
 * @brief Removes the matrix_t at the given index from the array. This shifts
 *        the other Matrices.
 *
 * @param index
 * @param matrix_array
 */
void matrix_array_remove_matrix(unsigned int index,
								matrix_array_t *matrix_array);

/**
 * @brief Get the matrix_t pointer from the array by value at the given index.
 *
 * @param index
 * @param matrix_array
 * @return matrix_t*
 */
matrix_t *matrix_array_get_matrix_pointer_by_value
		(unsigned int index, matrix_array_t *matrix_array);

/**
 * @brief Get the matrix_t pointer from the array by value at the given index.
 *
 * @param index
 * @param matrix_array
 * @return matrix_t**
 */
matrix_t **matrix_array_get_matrix_pointer_by_reference
		(unsigned int index, matrix_array_t *matrix_array);

/**
 * @brief Partitions the elements in the array in the given range for the quick
 *        sort algorithm based on the given pivot.
 *
 * @param pivot
 * @param first
 * @param last
 * @param cmp function used for sorting order
 * @return matrix_t**
 */
matrix_t **matrix_array_quick_sort_partition(matrix_t **pivot,
											 matrix_t **first,
											 matrix_t **last,
											 int (*cmp)(const matrix_t *,
														const matrix_t *));

/**
 * @brief Quick sorts the Matrices in the array in the given range
 *
 * @param first
 * @param last
 * @param cmp function used for sorting order
 */
void matrix_array_quick_sort(matrix_t **first, matrix_t **last,
							 int (*cmp)(const matrix_t *, const matrix_t *));

/**
 * @brief Doubles the capacity of the given matrix_array_t.
 *
 * @param matrix_array
 */
void matrix_array_double_capacity(matrix_array_t *matrix_array);

/**
 * @brief Halves the capacity of the given matrix_array_t.
 * @note Does not take into account the array's elements.
 *
 * @param matrix_array
 */
void matrix_array_half_capacity(matrix_array_t *matrix_array);

#endif
