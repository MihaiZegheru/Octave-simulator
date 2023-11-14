#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"

int main(void)
{
    setbuf(stdout, NULL);
    MatrixArray *matrix_array = new_matrix_array(0);

    printf("%p\n", matrix_array);
    // while (1) {
    //     char cmd;
    //     scanf("%c", &cmd);

    //     if (cmd == 'L') {
    //         // create new array pointer
    //     }
    // }

    delete_matrix_array(matrix_array);
}