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
    Matrix **matrices;
} MatrixArray;

/**
 * @brief Instantiates a new MatrixArray in memory and returns the pointer.
 * @note Can be instantiated with 0 capacity.
 * 
 * @param starting_capacity 
 * @return MatrixArray* 
 */
MatrixArray *new_matrix_array(unsigned int starting_capacity);
/**
 * @brief Deletes the given MatrixArray from memory.
 * 
 * @param matrix_array 
 */
void delete_matrix_array(MatrixArray *matrix_array);

/**
 * @brief Adds the given Matrix to the array as a pointer.
 * @note Adding the same matrix twice will result in two positions in the
 *       array pointing to the same matrix.
 * 
 * @param matrix 
 * @param matrix_array 
 */
void add_matrix(Matrix *matrix, MatrixArray *matrix_array);
/**
 * @brief Removes the Matrix at the given index from the array. This shifts
 *        the other Matrices.
 * 
 * @param index 
 * @param matrix_array 
 */
void remove_matrix(unsigned int index, MatrixArray *matrix_array);
/**
 * @brief Get the Matrix pointer from the array by value at the given index.
 * 
 * @param index 
 * @param matrix_array 
 * @return Matrix* 
 */
Matrix *get_matrix_pointer_by_value(unsigned int index, MatrixArray *matrix_array);
/**
 * @brief Get the Matrix pointer from the array by value at the given index.
 * 
 * @param index 
 * @param matrix_array 
 * @return Matrix** 
 */
Matrix **get_matrix_pointer_by_reference(unsigned int index, MatrixArray *matrix_array);

/**
 * @brief Partitions the elements in the array in the given range for the
 *        quick sort algorithm based on the given pivot.
 * 
 * @param pivot 
 * @param first 
 * @param last 
 * @param cmp function used for sorting order
 * @return Matrix** 
 */
Matrix **quick_sort_partition(Matrix **pivot, Matrix **first, Matrix **last, short int (*cmp)(const Matrix *, const Matrix *));
/**
 * @brief Quick sorts the Matrices in the array in the given range
 * 
 * @param first 
 * @param last 
 * @param cmp function used for sorting order
 */
void quick_sort(Matrix **first, Matrix **last, short int (*cmp)(const Matrix *, const Matrix *));

/**
 * @brief Doubles the capacity of the given MatrixArray.
 * 
 * @param matrix_array 
 */
void double_matrix_array_capacity(MatrixArray *matrix_array);
/**
 * @brief Halves the capacity of the given MatrixArray.
 * @note Does not take into account the array's elements.
 * 
 * @param matrix_array 
 */
void half_matrix_array_capacity(MatrixArray *matrix_array);

#endif
