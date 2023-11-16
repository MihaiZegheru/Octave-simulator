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

    printf("%p\n", matrix_array);
    while (1) {
        char cmd;
        scanf("%c", &cmd);

        if (cmd == 'L') {
            read_matrix_task(matrix_array);
        }
        if (cmd == 'P') {
            print_matrix_task(matrix_array);
        }
        if (cmd == 'D') {
            print_matrix_dimensions_task(matrix_array);
        }
        if (cmd == 'C') {
            resize_matrix_task(matrix_array);
        }
    }

    delete_matrix_array(matrix_array);
}