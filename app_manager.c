/*
 *   Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
 */

#include "app_manager.h"

void task_read_matrix(matrix_array_t *matrix_array)
{
	matrix_t *matrix = io_read_matrix();
	matrix_array_add_matrix(matrix, matrix_array);
}

void task_print_matrix(matrix_array_t *matrix_array)
{
	unsigned int index;
	scanf("%u", &index);

	matrix_t *matrix = matrix_array_get_matrix_pointer_by_value(index,
																matrix_array);
	if (!matrix) {
		printf("No matrix with the given index\n");
		return;
	}
	io_print_matrix(matrix);
}

void task_print_matrix_dimensions(matrix_array_t *matrix_array)
{
	unsigned int index;
	scanf("%u", &index);

	matrix_t *matrix = matrix_array_get_matrix_pointer_by_value(index,
																matrix_array);
	if (!matrix) {
		printf("No matrix with the given index\n");
		return;
	}
	printf("%u %u\n", matrix->size_n, matrix->size_m);
}

void task_resize_matrix(matrix_array_t *matrix_array)
{
	unsigned int index;
	scanf("%u", &index);

	unsigned int new_size_n;
	scanf("%u", &new_size_n);

	unsigned int *row_indexes = malloc(new_size_n * sizeof(int));
	if (!row_indexes)
		exit(-1);

	for (unsigned int i = 0 ; i < new_size_n; i++)
		scanf("%u", &row_indexes[i]);

	unsigned int new_size_m;
	scanf("%u", &new_size_m);

	unsigned int *col_indexes = malloc(new_size_m * sizeof(int));
	if (!col_indexes)
		exit(-1);

	for (unsigned int i = 0 ; i < new_size_m; i++)
		scanf("%u", &col_indexes[i]);

	matrix_t *matrix = matrix_array_get_matrix_pointer_by_value(index,
																matrix_array);
	if (!matrix) {
		printf("No matrix with the given index\n");

		free(row_indexes);
		free(col_indexes);
		return;
	}

	matrix_selective_resize(new_size_n, new_size_m, row_indexes, col_indexes,
							matrix);

	free(row_indexes);
	free(col_indexes);
}

void task_multiply_matrices(matrix_array_t *matrix_array)
{
	unsigned int index_a, index_b;
	scanf("%d%d", &index_a, &index_b);

	matrix_t *matrix_a = matrix_array_get_matrix_pointer_by_value(index_a,
																matrix_array);
	if (!matrix_a) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix_t *matrix_b = matrix_array_get_matrix_pointer_by_value(index_b,
																  matrix_array);
	if (!matrix_b) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix_t *result = matrix_multiply_matrices(matrix_a, matrix_b);
	if (!result) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	matrix_array_add_matrix(result, matrix_array);
}

void task_strassen_multiply_matrices(matrix_array_t *matrix_array)
{
	unsigned int index_a, index_b;
	scanf("%d%d", &index_a, &index_b);

	matrix_t *matrix_a = matrix_array_get_matrix_pointer_by_value(index_a,
																  matrix_array);
	if (!matrix_a) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix_t *matrix_b = matrix_array_get_matrix_pointer_by_value(index_b,
																  matrix_array);
	if (!matrix_b) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix_t *result = matrix_strassen_multiply_pot_matrices(matrix_a,
															 matrix_b);
	if (!result) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	matrix_array_add_matrix(result, matrix_array);
}

void task_sort_matrix_array(matrix_array_t *matrix_array)
{
	matrix_array_quick_sort(matrix_array->matrices,
							matrix_array->matrices + matrix_array->size - 1,
							matrix_cmp_matrices_ascending);
}

void task_transpose_matrix(matrix_array_t *matrix_array)
{
	unsigned int index;
	scanf("%d", &index);

	matrix_t *matrix = matrix_array_get_matrix_pointer_by_value(index,
																matrix_array);
	if (!matrix) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix_transpose(matrix);
}

void task_pow_raise_matrix(matrix_array_t *matrix_array)
{
	unsigned int index;
	scanf("%u", &index);

	int power;
	scanf("%d", &power);

	if (power < 0) {
		printf("Power should be positive\n");
		return;
	}

	matrix_t **matrix = matrix_array_get_matrix_pointer_by_reference
						(index, matrix_array);
	if (!matrix) {
		printf("No matrix with the given index\n");
		return;
	}

	if ((*matrix)->size_n != (*matrix)->size_m) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	matrix_power_raise((unsigned int)power, matrix);
}

void task_remove_matrix(matrix_array_t *matrix_array)
{
	unsigned int index;
	scanf("%u", &index);

	matrix_t **matrix = matrix_array_get_matrix_pointer_by_reference
								(index, matrix_array);
	if (!matrix) {
		printf("No matrix with the given index\n");
		return;
	}

	matrix_array_remove_matrix(index, matrix_array);
}

void task_quit(matrix_array_t *matrix_array)
{
	for (unsigned int i = 0; i < matrix_array->size; i++)
		matrix_delete(matrix_array_get_matrix_pointer_by_value(i,
															   matrix_array));

	matrix_array_delete(matrix_array);

	exit(0);
}
