#include "matrix_array.h"

#include "io_utils.h"

MatrixArray *new_matrix_array(unsigned int starting_capacity)
{
    MatrixArray *matrix_array = malloc(sizeof(MatrixArray));

    matrix_array->matrices = malloc(starting_capacity * sizeof(Matrix *)); 
    if (matrix_array->matrices == NULL && starting_capacity) {
        // err
    }

    matrix_array->capacity = starting_capacity;
    matrix_array->size = 0;

    return matrix_array;
}

void delete_matrix_array(MatrixArray *matrix_array)
{
    free(matrix_array->matrices);
    free(matrix_array);
}

void add_matrix(Matrix *matrix, MatrixArray *matrix_array)
{
    if (matrix_array->size + 1 >= matrix_array->capacity) {
        double_matrix_array_capacity(matrix_array);
    }

    matrix_array->matrices[matrix_array->size] = malloc(sizeof(Matrix *));
    if (matrix_array->matrices[matrix_array->size] == NULL) {
        // err
    }

    matrix_array->matrices[matrix_array->size] = matrix;
    matrix_array->size++;
}

Matrix *get_matrix_by_index(unsigned int index, MatrixArray *matrix_array)
{
    if (matrix_array->size == 0 || index > matrix_array->size - 1) {
        return NULL;
    }
    
    return matrix_array->matrices[index];
}

Matrix **quick_sort_partition(Matrix **pivot, Matrix **first, Matrix **last, short int (*cmp)(const Matrix *, const Matrix *))
{
    while (first - last <= 0) {
        while ((*cmp)(*first, *pivot)) {
            first++;
        }

        while (!(*cmp)(*last, *pivot)) {
            last--;
        }

        if (first - last <= 0) {
            swap_matrix_pointers(first, last);
            first++;
            last--;
        }
    }

    return first;
}

void quick_sort(Matrix **first, Matrix **last, short int (*cmp)(const Matrix *, const Matrix *))
{
    if (first >= last) {
        return;
    }

    Matrix **pivot = first + ((last - first) / 2);
    Matrix **partition = quick_sort_partition(pivot, first, last, cmp);

    quick_sort(first, partition - 1, cmp);
    quick_sort(partition, last, cmp);
}

void double_matrix_array_capacity(MatrixArray *matrix_array)
{
    if (matrix_array->capacity == 0) {
        matrix_array->capacity = 1;
    }
    else {
        matrix_array->capacity *= 2;
    }
    
    matrix_array->matrices = realloc(matrix_array->matrices,
                                     matrix_array->capacity * sizeof(int*));

    if (matrix_array->matrices == NULL) {
        // err
    }
}
