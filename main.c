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
            print_matrix(matrix);
        }
        if (cmd == 'D') {
            unsigned int index;
            scanf("%u", &index);

            Matrix *matrix = get_matrix_by_index(index, matrix_array);
            printf("%u %u\n", matrix->size_n, matrix->size_m);
        }
    }

    delete_matrix_array(matrix_array);
}