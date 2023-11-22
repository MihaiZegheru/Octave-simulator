#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

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
} Matrix;

/**
 * @brief Instantiates a new Matrix in memory and returns the pointer.
 * 
 * @param size_n 
 * @param size_m 
 * @return Matrix* 
 */
Matrix *new_matrix(unsigned int size_n, unsigned int size_m);

/**
 * @brief Deletes the given Matrix from memory.
 * 
 * @param matrix 
 */
void delete_matrix(Matrix *matrix);

/**
 * @brief Resizes the given Matrix including the intersection of the specified
 *        rows and columns.
 * 
 * @param new_size_n 
 * @param new_size_m 
 * @param row_indexes array with row indexes to include
 * @param col_indexes array with column indexes to include
 * @param matrix 
 */
void resize(unsigned int new_size_n, unsigned int new_size_m,
            unsigned int *row_indexes, unsigned int *col_indexes,
            Matrix *matrix);
            
/**
 * @brief Multiplies two given Matrices and returns the new one.
 * 
 * @param matrix_a 
 * @param matrix_b 
 * @return Matrix* 
 */
Matrix *multiply_matrices(Matrix *matrix_a, Matrix *matrix_b);

/**
 * @brief Multiplies two given Matrices using Strassen's algorithm and returns a
 *        new one.
 * 
 * @param matrix_a 
 * @param matrix_b 
 * @return Matrix* 
 */
Matrix *strassen_multiply_pot_matrices(Matrix *matrix_a, Matrix *matrix_b);

/**
 * @brief Transposes the given Matrix and saves it at the same address.
 * 
 * @param matrix 
 */
void transpose_matrix(Matrix *matrix);

/**
 * @brief Interface for raising the given Matrix to a power in logarithmic time
 *        and saves it at the same address.
 * 
 * @param power 
 * @param matrix 
 */
void power_raise_matrix(unsigned int power, Matrix **matrix);


/**
 * @brief Adds two Matrices and returns the result as a new Matrix.
 * 
 * @param a 
 * @param b 
 * @return Matrix* 
 */
Matrix *add_matrices(Matrix *a, Matrix *b);

/**
 * @brief Subtracts two Matrices and returns the result as a new Matrix.
 * 
 * @param a 
 * @param b 
 * @return Matrix* 
 */
Matrix *subtract_matrices(Matrix *a, Matrix *b);

/**
 * @brief Swaps two Matrices.
 * 
 * @param a 
 * @param b 
 */
void swap_matrices(Matrix **a, Matrix **b);

/**
 * @brief Resizes the given Matrix, ignoring the old values.
 * 
 * @param new_size_n 
 * @param new_size_m 
 * @param matrix 
 */
void resize_matrix(unsigned int new_size_n, unsigned int new_size_m,
                   Matrix *matrix);

/**
 * @brief Breaks the given Matrix in 4 equal square blocks. Returns through parameters.
 * @note The specified matrix must have equal sizes, powers of two.
 * 
 * @param matrix 
 * @param a returned block matrix address
 * @param b returned block matrix address
 * @param c returned block matrix address
 * @param d returned block matrix address
 */
void break_matrix_in_blocks(Matrix *matrix, Matrix **a, Matrix **b, Matrix **c,
                            Matrix **d);

/**
 * @brief Builds a Matrix from 4 smaller blocks. Returns a new Matrix.
 * @note The building blocks must all have equal sizes, powers of two.
 * 
 * @param a
 * @param b 
 * @param c 
 * @param d 
 * @return Matrix* 
 */
Matrix *build_matrix_from_blocks(Matrix *a, Matrix *b, Matrix *c, Matrix *d);

/**
 * @brief The implementation of logarithmic power raising. Returns result Matrix as parameter.
 * 
 * @param power 
 * @param matrix 
 * @param result_matrix 
 */
void recursive_power_raise_matrix(unsigned int power, Matrix *matrix,
                                  Matrix **result_matrix);

/**
 * @brief Calculates the sum of all the elements of the matrix.
 * @note The sum is modulo.
 * 
 * @param *matrix: 
 * @return int
 */
int compute_elements_sum(const Matrix *matrix);

/**
 * @brief Calculates the difference between Matrix a and Matrix b;
 *        if a > b returns -1, else returns 0.
 * @note Used for sorting algorithms.
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp_matrices_ascending(const Matrix *a, const Matrix *b);

/**
 * @brief Calculates the difference between Matrix b and Matrix a;
 * @note Used for sorting algorithms.
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmp_matrices_descending(const Matrix *a, const Matrix *b);

/**
 * @brief Applies modulo on given value and returns new value.
 * @note Used for overflow protection.
 * @note MODULO = 10007
 * 
 * @param value 
 * @return int 
 */
int modulo(int value);

#endif
