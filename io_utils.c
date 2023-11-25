#include "io_utils.h"

matrix_t *io_read_matrix(void)
{
	// Does not check for mistakes in input

	unsigned int size_n, size_m;
	scanf("%u%u", &size_n, &size_m);

	matrix_t *matrix = matrix_new(size_n, size_m);

	for (unsigned int i = 0; i < size_n; i++)
		for (unsigned int j = 0; j < size_m; j++)
			scanf("%d", &matrix->values[i][j]);

	matrix_update_elements_sum(matrix);

	return matrix;
}

void io_print_matrix(matrix_t *matrix)
{
	for (unsigned int i = 0; i < matrix->size_n; i++) {
		for (unsigned int j = 0; j < matrix->size_m; j++)
			printf("%d ", matrix->values[i][j]);
		printf("\n");
	}
}
