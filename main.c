#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"
#include "io_utils.h"
#include "app_manager.h"

int main(void)
{
    setbuf(stdout, NULL);
    MatrixArray *matrix_array = new_matrix_array(0);

    while (1) {
        char cmd;
        scanf("%c", &cmd);

        if (cmd == ' ' || cmd == '\n')
        {
            continue;
        }

        if (cmd == 'L') {
            read_matrix_task(matrix_array);
            continue;
        }
        if (cmd == 'P') {
            print_matrix_task(matrix_array);
            continue;
        }
        if (cmd == 'D') {
            print_matrix_dimensions_task(matrix_array);
            continue;
        }
        if (cmd == 'C') {
            resize_matrix_task(matrix_array);
            continue;
        }
        if (cmd == 'M') {
            multiply_matrices_task(matrix_array);
            continue;
        }
        if (cmd == 'O') {
            sort_matrix_array_task(matrix_array);
            continue;
        }
        if (cmd == 'T') {
            transpose_matrix_task(matrix_array);
            continue;
        }
        if (cmd == 'R') {
            pow_raise_matrix_task(matrix_array);
            continue;
        }
        if (cmd == 'F') {
            remove_matrix_task(matrix_array);
            continue;
        }
        if (cmd == 'Q') {
            quit(matrix_array);
            continue;
        }

        printf("Unrecognized command\n");
    }

    // TODO 1: add modulo
    // TODO 2: add unrec cmd


    delete_matrix_array(matrix_array);
}