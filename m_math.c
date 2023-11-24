#include "matrix.h"

matrix_t *matrix_math_add_matrices(matrix_t *a, matrix_t *b)
{
	if (a->size_n != b->size_n || a->size_m != b->size_m)
		return NULL;

	matrix_t *matrix = matrix_new(a->size_n, a->size_m);
	for (unsigned int i = 0; i < a->size_n; i++)
		for (unsigned int j = 0; j < a->size_m; j++)
			matrix->values[i][j] = modulo(a->values[i][j] + b->values[i][j]);

	return matrix;
}

matrix_t *matrix_math_subtract_matrices(matrix_t *a, matrix_t *b)
{
	if (a->size_n != b->size_n || a->size_m != b->size_m)
		return NULL;

	matrix_t *matrix = matrix_new(a->size_n, a->size_m);
	for (unsigned int i = 0; i < a->size_n; i++)
		for (unsigned int j = 0; j < a->size_m; j++)
			matrix->values[i][j] = modulo(a->values[i][j] - b->values[i][j]);

	return matrix;
}
