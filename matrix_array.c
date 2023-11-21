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

// This function offers an interface for adding a matrix to the array.
// 
// If the size of the array becomes greater than the capacity, it will firstly
// double the capacity.
void add_matrix(Matrix *matrix, MatrixArray *matrix_array)
{
    if (matrix_array->size + 1 >= matrix_array->capacity) {
        double_matrix_array_capacity(matrix_array);
    }

    matrix_array->matrices[matrix_array->size] = matrix;
    matrix_array->size++;
}

// This function offers an interface for removing a matrix from the array.
// 
// If the size of the array is less or half the capacity, the capacity will be
// halved.
void remove_matrix(unsigned int index, MatrixArray *matrix_array)
{
    if (index >= matrix_array->size) {
        // err
    }

    Matrix *matrix = get_matrix_pointer_by_value(index, matrix_array);
    delete_matrix(matrix);

    for (unsigned int i = index; i < matrix_array->size; i++) {
        matrix_array->matrices[i] = matrix_array->matrices[i + 1];
    }

    matrix_array->size--;

    if (matrix_array->size <= matrix_array->capacity / 2) {
        half_matrix_array_capacity(matrix_array);
    }
}

Matrix *get_matrix_pointer_by_value(unsigned int index,
                                    MatrixArray *matrix_array)
{
    if (matrix_array->size == 0 || index > matrix_array->size - 1) {
        return NULL;
    }
    
    return matrix_array->matrices[index];
}

Matrix **get_matrix_pointer_by_reference(unsigned int index,
                                         MatrixArray *matrix_array)
{
    if (matrix_array->size == 0 || index > matrix_array->size - 1) {
        return NULL;
    }
    
    return &matrix_array->matrices[index];
}

// This function represents the core functionality part of the quick sort
// algorithm. It returns the partition index.
Matrix **quick_sort_partition(Matrix **pivot, Matrix **first, Matrix **last,
                              short int (*cmp)(const Matrix *, const Matrix *))
{
    while (first - last <= 0) {
        while ((*cmp)(*first, *pivot) == 1) {
            first++;
        }

        while ((*cmp)(*last, *pivot) == -1) {
            last--;
        }

        if (first - last <= 0) {
            swap_matrices(first, last);
            first++;
            last--;
        }
    }

    return first;
}

// This function offers the implementation of a quick sort on a matrix array.
// The quick sort algorithm takes a pivot and it checks for the bigger elements 
// at its left and for the smaller elements at its right and then swaps them.
// After all the swaps have been done, it partitions the array into two smaller
// ones, repeating the algorithm recursively.
void quick_sort(Matrix **first, Matrix **last,
                short int (*cmp)(const Matrix *,const Matrix *))
{
    if (first >= last) {
        return;
    }

    Matrix **pivot = first + ((last - first) / 2);
    Matrix **partition = quick_sort_partition(pivot, first, last, cmp);

    quick_sort(first, partition - 1, cmp);
    quick_sort(partition, last, cmp);
}

// This function takes a matrix array and it doubles the capacity without taking
// into consideration the already existing values.
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

// This function takes a matrix array and it halves the capacity without taking
// into consideration the already existing values.
void half_matrix_array_capacity(MatrixArray *matrix_array)
{
    matrix_array->capacity /= 2;
    if(matrix_array->capacity == 0) {
        matrix_array->capacity = 1;
    }
    
    matrix_array->matrices = realloc(matrix_array->matrices,
                                     matrix_array->capacity * sizeof(int*));
    
    if (matrix_array->matrices == NULL) {
        exit(-1);
    }
}
