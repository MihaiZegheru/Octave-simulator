#include "matrix_array.h"

#include "io_utils.h"

MatrixArray *new_matrix_array(unsigned int starting_capacity)
{
    MatrixArray *matrix_array = malloc(sizeof(MatrixArray));

    matrix_array->matrices = malloc(starting_capacity * sizeof(Matrix *)); 
    if (matrix_array->matrices == NULL && starting_capacity) {
        exit(-1);
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
        exit(-1);
    }

    matrix_array->matrices[matrix_array->size] = matrix;
    matrix_array->size++;
}

void remove_matrix(unsigned int index, MatrixArray *matrix_array)
{
    if (index >= matrix_array->size) {
        // err
    }

    Matrix *matrix = get_matrix_by_value(index, matrix_array);
    delete_matrix(matrix);

    for (unsigned int i = index; i < matrix_array->size; i++) {
        matrix_array->matrices[i] = matrix_array->matrices[i + 1];
    }

    matrix_array->size--;

    if (matrix_array->size <= matrix_array->capacity / 2) {
        half_matrix_array_capacity(matrix_array);
    }
}

Matrix *get_matrix_by_value(unsigned int index, MatrixArray *matrix_array)
{
    if (matrix_array->size == 0 || index > matrix_array->size - 1) {
        return NULL;
    }
    
    return matrix_array->matrices[index];
}

Matrix **get_matrix_by_reference(unsigned int index, MatrixArray *matrix_array)
{
    if (matrix_array->size == 0 || index > matrix_array->size - 1) {
        return NULL;
    }
    
    return &matrix_array->matrices[index];
}

Matrix **quick_sort_partition(Matrix **pivot, Matrix **first, Matrix **last, short int (*cmp)(const Matrix *, const Matrix *))
{
    while (first - last <= 0) {
        while ((*cmp)(*first, *pivot) == 1) {
            first++;
        }

        while ((*cmp)(*last, *pivot) == -1) {
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
        exit(-1);
    }
}

void half_matrix_array_capacity(MatrixArray *matrix_array)
{
    matrix_array->capacity /= 2;
    matrix_array->matrices = realloc(matrix_array->matrices,
                                     matrix_array->capacity * sizeof(int*));

    if (matrix_array->matrices == NULL) {
        exit(-1);
    }
}
