#include "matrix_array.h"

#include "io_utils.h"

matrix_array_t *matrix_array_new(unsigned int starting_capacity)
{
	matrix_array_t *matrix_array = malloc(sizeof(matrix_array_t));

	matrix_array->matrices = malloc(starting_capacity * sizeof(matrix_t *));
	if (!matrix_array->matrices && starting_capacity)
		exit(-1);

	matrix_array->capacity = starting_capacity;
	matrix_array->size = 0;

	return matrix_array;
}

void matrix_array_delete(matrix_array_t *matrix_array)
{
	free(matrix_array->matrices);
	free(matrix_array);
}

// This function offers an interface for adding a matrix to the array.
//
// If the size of the array becomes greater than the capacity, it will firstly
// double the capacity.
void matrix_array_add_matrix(matrix_t *matrix, matrix_array_t *matrix_array)
{
	if (matrix_array->size + 1 >= matrix_array->capacity)
		matrix_array_double_capacity(matrix_array);

	matrix_array->matrices[matrix_array->size] = matrix;
	matrix_array->size++;
}

// This function offers an interface for removing a matrix from the array.
//
// If the size of the array is less or half the capacity, the capacity will be
// halved.
void matrix_array_remove_matrix(unsigned int index,
								matrix_array_t *matrix_array)
{
	if (index >= matrix_array->size)
		exit(-1);

	matrix_t *matrix = matrix_array_get_matrix_pointer_by_value
			(index, matrix_array);
	matrix_delete(matrix);

	matrix_array->size--;

	for (unsigned int i = index; i < matrix_array->size; i++)
		matrix_array->matrices[i] = matrix_array->matrices[i + 1];

	if (matrix_array->size <= matrix_array->capacity / 2)
		matrix_array_half_capacity(matrix_array);
}

matrix_t *matrix_array_get_matrix_pointer_by_value(unsigned int index,
												   matrix_array_t *matrix_array)
{
	if (matrix_array->size == 0 || index > matrix_array->size - 1)
		return NULL;

	return matrix_array->matrices[index];
}

matrix_t **matrix_array_get_matrix_pointer_by_reference
		(unsigned int index, matrix_array_t *matrix_array)
{
	if (matrix_array->size == 0 || index > matrix_array->size - 1)
		return NULL;

	return &matrix_array->matrices[index];
}

// This function represents the core functionality part of the quick sort
// algorithm. It returns the partition index.
matrix_t **matrix_array_quick_sort_partition(matrix_t **pivot,
											 matrix_t **first,
											 matrix_t **last,
											 int (*cmp)(const matrix_t *,
														const matrix_t *))
{
	// TODO: Add pivot randomisation and change quick sort implementation for
	//       better optimisation
	pivot = last;
	matrix_t **iterator_1 = first;

	for (matrix_t **iterator_2 = first; iterator_2 < last; iterator_2++) {
		if ((*cmp)(*iterator_2, *pivot) <= 0) {
			matrix_swap_matrices(iterator_1, iterator_2);

			iterator_1++;
		}
	}

	matrix_swap_matrices(iterator_1, last);

	return iterator_1;
}

// This function offers the implementation of a quick sort on a matrix array.
// This quick sort algorithm picks a pivot at the last position. It then
// iterates (second iterator) through the elements in the partition and swaps
// them if the second iterator points to a bigger value than the pivot. It then
// increses the first iterator.
void matrix_array_quick_sort(matrix_t **first, matrix_t **last,
							 int (*cmp)(const matrix_t *, const matrix_t *))
{
	if (first >= last)
		return;

	matrix_t **pivot = first + ((last - first) / 2);
	matrix_t **partition = matrix_array_quick_sort_partition(pivot, first, last,
														   cmp);

	matrix_array_quick_sort(first, partition - 1, cmp);
	matrix_array_quick_sort(partition, last, cmp);
}

// This function takes a matrix array and it doubles the capacity without taking
// into consideration the already existing values.
void matrix_array_double_capacity(matrix_array_t *matrix_array)
{
	if (matrix_array->capacity == 0)
		matrix_array->capacity = 1;
	else
		matrix_array->capacity *= 2;

	matrix_array->matrices = realloc(matrix_array->matrices,
									 matrix_array->capacity * sizeof(int *));

	if (!matrix_array->matrices)
		exit(-1);
}

// This function takes a matrix array and it halves the capacity without taking
// into consideration the already existing values.
void matrix_array_half_capacity(matrix_array_t *matrix_array)
{
	matrix_array->capacity /= 2;
	if (matrix_array->capacity == 0)
		matrix_array->capacity = 1;

	matrix_array->matrices = realloc(matrix_array->matrices,
									 matrix_array->capacity * sizeof(int *));

	if (!matrix_array->matrices)
		exit(-1);
}
