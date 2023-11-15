#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"
#include "io_handle.h"

int main(void)
{
    setbuf(stdout, NULL);
    MatrixArray *matrix_array = new_matrix_array(0);

    printf("%p\n", matrix_array);
    while (1) {
        char cmd;
        scanf("%c", &cmd);

        if (cmd == 'L') {
            add_matrix(matrix_array);
        }

        if (cmd == 'P') {
            unsigned int index;
            scanf("%u", &index);

            Matrix *matrix = get_matrix_by_index(index, matrix_array);
            if (matrix == NULL) {
                printf("No matrix with the given index");
                continue;
            }
            print_matrix(matrix);
        }

        if (cmd == 'D') {
            unsigned int index;
            scanf("%u", &index);

            Matrix *matrix = get_matrix_by_index(index, matrix_array);
            if (matrix == NULL) {
                printf("No matrix with the given index");
                continue;
            }
            printf("%u %u\n", matrix->size_n, matrix->size_m);
        }

        if (cmd == 'C') {
            unsigned int index;
            scanf("%u", &index);

            unsigned int new_size_n;
            scanf("%u", &new_size_n);

            unsigned int *row_indexes = malloc(new_size_n * sizeof(int));
            for (unsigned int i = 0 ; i < new_size_n; i++) {
                scanf("%u", &row_indexes[i]);
                row_indexes[i]--;
            }

            unsigned int new_size_m;
            scanf("%u", &new_size_m);

            unsigned int *col_indexes = malloc(new_size_m * sizeof(int));
            for (unsigned int i = 0 ; i < new_size_m; i++) {
                scanf("%u", &col_indexes[i]);
                col_indexes[i]--;
            }

            Matrix *matrix = get_matrix_by_index(index, matrix_array);
            if (matrix == NULL) {
                printf("No matrix with the given index");

                free(row_indexes);
                free(col_indexes);
                continue;
            }

            resize(new_size_n, new_size_m, row_indexes, col_indexes, matrix);

            free(row_indexes);
            free(col_indexes);
        }
    }

    delete_matrix_array(matrix_array);
}