#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "matrix_array.h"
#include "io_utils.h"
#include "app_manager.h"

int main(void)
{
	setbuf(stdout, NULL);
	matrix_array_t *matrix_array = matrix_array_new(0);

	while (1) {
		char cmd;
		scanf("%c", &cmd);

		if (cmd == ' ' || cmd == '\n')
			continue;

		if (cmd == 'L') {
			task_read_matrix(matrix_array);
			continue;
		}
		if (cmd == 'P') {
			task_print_matrix(matrix_array);
			continue;
		}
		if (cmd == 'D') {
			task_print_matrix_dimensions(matrix_array);
			continue;
		}
		if (cmd == 'C') {
			task_resize_matrix(matrix_array);
			continue;
		}
		if (cmd == 'M') {
			task_multiply_matrices(matrix_array);
			continue;
		}
		if (cmd == 'S') {
			task_strassen_multiply_matrices(matrix_array);
			continue;
		}
		if (cmd == 'O') {
			task_sort_matrix_array(matrix_array);
			continue;
		}
		if (cmd == 'T') {
			task_transpose_matrix(matrix_array);
			continue;
		}
		if (cmd == 'R') {
			task_pow_raise_matrix(matrix_array);
			continue;
		}
		if (cmd == 'F') {
			task_remove_matrix(matrix_array);
			continue;
		}
		if (cmd == 'Q') {
			task_quit(matrix_array);
			continue;
		}

		printf("Unrecognized command\n");
	}

	matrix_array_delete(matrix_array);
}
