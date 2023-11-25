#include "matrix.h"

matrix_t *matrix_new(unsigned int size_n, unsigned int size_m)
{
	matrix_t *matrix = malloc(sizeof(matrix_t));
	matrix->size_n = size_n;
	matrix->size_m = size_m;

	matrix->values = malloc(size_n * sizeof(int *));
	if (!matrix->values)
		exit(-1);

	for (unsigned int i = 0; i < size_n; i++) {
		matrix->values[i] = malloc(size_m * sizeof(int));
		if (!matrix->values[i])
			exit(-1);
	}

	return matrix;
}

void matrix_delete(matrix_t *matrix)
{
	for (unsigned int i = 0; i < matrix->size_n; i++)
		free(matrix->values[i]);

	free(matrix->values);
	free(matrix);
}

// This function offers an interface for resizing a given matrix to the given
// sizes by selecting what values to include in the result and saving it at the
// same address.
//
// This function firstly creates a new auxilary matrix with the new sizes. It
// then sets in the values following the rule: it combines the indexes 2 by 2 in
// the rows array with the ones in the columns array and saves the value at the
// indexes in the auxilary matrix. After this, the old matrix gets resized to
// the new values and the contants of the auxilary matrix are moved into the
// original one. In the end, the auxilary matrix gets deleted.
void matrix_selective_resize(unsigned int new_size_n, unsigned int new_size_m,
							 unsigned int *row_indexes,
							 unsigned int *col_indexes,
							 matrix_t *matrix)
{
	matrix_t *aux_matrix = matrix_new(new_size_n, new_size_m);
	for (unsigned int i = 0; i < new_size_n; i++) {
		for (unsigned int j = 0; j < new_size_m; j++) {
			unsigned int index_i = row_indexes[i];
			unsigned int index_j = col_indexes[j];

			aux_matrix->values[i][j] = matrix->values[index_i][index_j];
		}
	}

	matrix_resize(new_size_n, new_size_m, matrix);

	for (unsigned int i = 0; i < new_size_n; i++)
		for (unsigned int j = 0; j < new_size_m; j++)
			matrix->values[i][j] = aux_matrix->values[i][j];
	matrix_update_elements_sum(matrix);
	
	matrix_delete(aux_matrix);
}

// This functions implements basic matrix multiplication.
//
// This function firstly creates a new matrix for storing the resulted matrix.
// It then performs the operations, adding the resulted values to the new
// matrix. At the end, it returns the new matrix' pointer.
matrix_t *matrix_multiply_matrices(matrix_t *matrix_a, matrix_t *matrix_b)
{
	if (matrix_a->size_m != matrix_b->size_n)
		return NULL;

	unsigned int common_size = matrix_a->size_m;
	unsigned int new_size_n = matrix_a->size_n;
	unsigned int new_size_m = matrix_b->size_m;

	matrix_t *result = matrix_new(new_size_n, new_size_m);

	for (unsigned int i = 0; i < new_size_n; i++) {
		for (unsigned int j = 0; j < new_size_m; j++) {
			int sum = 0;
			for (unsigned int k = 0; k < common_size; k++)
				sum = modulo(sum + matrix_a->values[i][k] *
							 matrix_b->values[k][j]);

			result->values[i][j] = sum;
		}
	}

	matrix_update_elements_sum(result);

	return result;
}

// This function implements matrix multiplication recursively, using Strassen's
// algorithm. This algorithm is based on the divide et impera at its core,
// breaking matrices in basic building blocks and then performing operations on
// them. For simplicity this implementation works only for matrices that have
// equal sizes that are powers of two.
//
// The function firstly breaks the given matrix into blocks. It then calculates
// using Strassen's formulas new matrices and then builds back the result of
// multiplication.
// The exit condition is reached when the givem matrix becomes a singular block
// of size one.
matrix_t *matrix_strassen_multiply_pot_matrices(matrix_t *matrix_a,
												matrix_t *matrix_b)
{
	// This implemntation works on matrices that have a size of 2^n
	if (matrix_a->size_m != matrix_b->size_n)
		return NULL;

	if (matrix_a->size_n == 1)
		return matrix_multiply_matrices(matrix_a, matrix_b);

	matrix_t *a1, *a2, *a3, *a4;
	matrix_break_in_blocks(matrix_a, &a1, &a2, &a3, &a4);

	matrix_t *b1, *b2, *b3, *b4;
	matrix_break_in_blocks(matrix_b, &b1, &b2, &b3, &b4);

	matrix_t *m1 = matrix_strassen_compute_m1(a1, a4, b1, b4);
	matrix_t *m2 = matrix_strassen_compute_m2(a3, a4, b1);
	matrix_t *m3 = matrix_strassen_compute_m3(a1, b2, b4);
	matrix_t *m4 = matrix_strassen_compute_m4(a4, b1, b3);
	matrix_t *m5 = matrix_strassen_compute_m5(a1, a2, b4);
	matrix_t *m6 = matrix_strassen_compute_m6(a1, a3, b1, b2);
	matrix_t *m7 = matrix_strassen_compute_m7(a2, a4, b3, b4);

	matrix_t *c1 = matrix_strassen_compute_c1(m1, m4, m5, m7);
	matrix_t *c2 = matrix_strassen_compute_c2(m3, m5);
	matrix_t *c3 = matrix_strassen_compute_c3(m2, m4);
	matrix_t *c4 = matrix_strassen_compute_c4(m1, m2, m3, m6);

	matrix_t *result = matrix_build_from_blocks(c1, c2, c3, c4);

	matrix_delete(c1);
	matrix_delete(c2);
	matrix_delete(c3);
	matrix_delete(c4);

	matrix_delete(m7);
	matrix_delete(m6);
	matrix_delete(m5);
	matrix_delete(m4);
	matrix_delete(m3);
	matrix_delete(m2);
	matrix_delete(m1);

	matrix_delete(a1);
	matrix_delete(a2);
	matrix_delete(a3);
	matrix_delete(a4);

	matrix_delete(b1);
	matrix_delete(b2);
	matrix_delete(b3);
	matrix_delete(b4);

	matrix_update_elements_sum(result);

	return result;
}

// This function transposes a givem matrix and saves it at the same address.
//
// It first creates an auxilary matrix that has the required sizes, so that the
// new number of rows is equal to the original number of columns and vice verse.
// It then copies the values respectively into the auxilary matrix and resizes
// the original matrix. At the end, it copies the values back into the original
// matrix and deletes the auxilary matrix.
void matrix_transpose(matrix_t *matrix)
{
	unsigned int new_size_n = matrix->size_m;
	unsigned int new_size_m = matrix->size_n;

	matrix_t *aux_matrix = matrix_new(new_size_n, new_size_m);

	for (unsigned int i = 0; i < new_size_n; i++)
		for (unsigned int j = 0; j < new_size_m; j++)
			aux_matrix->values[i][j] = matrix->values[j][i];

	matrix_resize(new_size_n, new_size_m, matrix);

	for (unsigned int i = 0; i < new_size_n; i++)
		for (unsigned int j = 0; j < new_size_m; j++)
			matrix->values[i][j] = aux_matrix->values[i][j];
	matrix_update_elements_sum(matrix);

	matrix_delete(aux_matrix);
}

// This function raises a matrix to a power in logarithmic time. It makes use of
// the mathematical formula a^2n = a^n * a^n.
//
// If the power is even, it will call itself recursively with the power divided
// by two and then multiply the resulted matrices. If the power is odd, it will
// call itself recursively with the power - 1 and then multiply the result with
// the original matrix.
// The exit condition is reached when the power becomes equal to 0. Then, the
// function returns the identity matrix.
void matrix_recursive_power_raise(unsigned int power, matrix_t *matrix,
								  matrix_t **result_matrix)
{
	if (power == 0) {
		for (unsigned int i = 0; i < matrix->size_n; i++) {
			for (unsigned int j = 0; j < matrix->size_m; j++) {
				if (i == j)
					(*result_matrix)->values[i][j] = 1;
				else
					(*result_matrix)->values[i][j] = 0;
			}
		}

		return;
	}

	if (power % 2) {
		matrix_recursive_power_raise(power - 1, matrix, result_matrix);
		matrix_t *matrix_new = matrix_multiply_matrices(matrix, *result_matrix);

		matrix_delete(*result_matrix);
		*result_matrix = matrix_new;
	} else {
		matrix_recursive_power_raise(power / 2, matrix, result_matrix);
		matrix_t *matrix_new = matrix_multiply_matrices(*result_matrix,
														*result_matrix);

		matrix_delete(*result_matrix);
		*result_matrix = matrix_new;
	}
}

// This function offers an interface for rasising a given matrix to a given
// power and storing it at the same address.
void matrix_power_raise(unsigned int power, matrix_t **matrix)
{
	matrix_t *result_matrix = matrix_new((*matrix)->size_n, (*matrix)->size_m);
	matrix_recursive_power_raise(power, *matrix, &result_matrix);

	matrix_delete(*matrix);
	*matrix = result_matrix;

	matrix_update_elements_sum(matrix);
}

// This functions swaps two matrices' pointers.
void matrix_swap_matrices(matrix_t **a, matrix_t **b)
{
	matrix_t *aux = *a;
	*a = *b;
	*b = aux;
}

// This function resizes a matrix by the given sizes. It does not take into
// account the already existing values in the matrix.
//
// This function firstly clears all the memory that would exceed the new bounds
// and then in reallocates or allocates the new memory.
void matrix_resize(unsigned int new_size_n, unsigned int new_size_m,
				   matrix_t *matrix)
{
	for (unsigned int i = 0; i < matrix->size_n; i++)
		free(matrix->values[i]);

	matrix->size_n = new_size_n;
	matrix->size_m = new_size_m;

	matrix->values = realloc(matrix->values, new_size_n * sizeof(int *));
	if (!matrix->values)
		exit(-1);

	for (unsigned int i = 0; i < new_size_n; i++) {
		matrix->values[i] = malloc(new_size_m * sizeof(int));
		continue;
		// TODO: fix this
		if (!matrix->values[i])
			exit(-1);
		else
			matrix->values[i] = realloc(matrix->values[i],
										new_size_m * sizeof(int));
	}
}

void matrix_break_in_blocks(matrix_t *matrix, matrix_t **a, matrix_t **b,
							matrix_t **c,
							matrix_t **d)
{
	unsigned int new_size_n = matrix->size_n / 2;
	unsigned int new_size_m = matrix->size_m / 2;

	*a = matrix_new(new_size_n, new_size_m);
	*b = matrix_new(new_size_n, new_size_m);
	*c = matrix_new(new_size_n, new_size_m);
	*d = matrix_new(new_size_n, new_size_m);

	for (unsigned int i = 0; i < new_size_n; i++) {
		for (unsigned int j = 0; j < new_size_m; j++) {
			(*a)->values[i][j] = matrix->values[i][j];
			(*b)->values[i][j] = matrix->values[i][new_size_m + j];
			(*c)->values[i][j] = matrix->values[new_size_n + i][j];
			(*d)->values[i][j] = matrix->values[new_size_n + i][new_size_m + j];
		}
	}
}

matrix_t *matrix_build_from_blocks(matrix_t *a, matrix_t *b, matrix_t *c,
								   matrix_t *d)
{
	unsigned int new_size_n = a->size_n + c->size_n;
	unsigned int new_size_m = a->size_m + b->size_m;

	matrix_t *matrix = matrix_new(new_size_n, new_size_m);

	for (unsigned int i = 0; i < a->size_n; i++) {
		for (unsigned int j = 0; j < a->size_m; j++) {
			matrix->values[i][j] = a->values[i][j];
			matrix->values[i][a->size_m + j] = b->values[i][j];
			matrix->values[a->size_n + i][j] = c->values[i][j];
			matrix->values[a->size_n + i][a->size_m + j] = d->values[i][j];
		}
	}

	return matrix;
}

void matrix_update_elements_sum(matrix_t *matrix)
{
	int sum = 0;

	for (unsigned int i = 0; i < matrix->size_n; i++)
		for (unsigned int j = 0; j < matrix->size_m; j++)
			sum = modulo(sum + matrix->values[i][j]);

	matrix->sum = sum;
}

int matrix_cmp_matrices_ascending(const matrix_t *a, const matrix_t *b)
{
	return a->sum - b->sum;
}

int matrix_cmp_matrices_descending(const matrix_t *a, const matrix_t *b)
{
	return b->sum - a->sum;
}
