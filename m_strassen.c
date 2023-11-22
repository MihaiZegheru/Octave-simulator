#include "matrix.h"

#include "m_math.c"

matrix_t *matrix_strassen_compute_m1(matrix_t *a1, matrix_t *a4, matrix_t *b1, 
                                     matrix_t *b4)
{
    matrix_t *add_a1_a4 = matrix_math_add_matrices(a1, a4);
	matrix_t *add_b1_b4 = matrix_math_add_matrices(b1, b4);
	matrix_t *m1 = matrix_strassen_multiply_pot_matrices(add_a1_a4, add_b1_b4);
	matrix_delete(add_b1_b4);
	matrix_delete(add_a1_a4);

    return m1;
}

matrix_t *matrix_strassen_compute_m2(matrix_t *a3, matrix_t *a4, matrix_t *b1)
{
    matrix_t *add_a3_a4 = matrix_math_add_matrices(a3, a4);
	matrix_t *m2 = matrix_strassen_multiply_pot_matrices(add_a3_a4, b1);
	matrix_delete(add_a3_a4);

    return m2;
}

matrix_t *matrix_strassen_compute_m3(matrix_t *a1, matrix_t *b2, matrix_t *b4)
{
    matrix_t *sub_b2_b4 = matrix_math_subtract_matrices(b2, b4);
	matrix_t *m3 = matrix_strassen_multiply_pot_matrices(a1, sub_b2_b4);
	matrix_delete(sub_b2_b4);

    return m3;
}

matrix_t *matrix_strassen_compute_m4(matrix_t *a4, matrix_t *b1, matrix_t *b3)
{
	matrix_t *sub_b3_b1 = matrix_math_subtract_matrices(b3, b1);
	matrix_t *m4 = matrix_strassen_multiply_pot_matrices(a4, sub_b3_b1);
	matrix_delete(sub_b3_b1);

    return m4;
}

matrix_t *matrix_strassen_compute_m5(matrix_t *a1, matrix_t *a2, matrix_t *b4)
{
	matrix_t *add_a1_a2 = matrix_math_add_matrices(a1, a2);
	matrix_t *m5 = matrix_strassen_multiply_pot_matrices(add_a1_a2, b4);
	matrix_delete(add_a1_a2);

    return m5;
}

matrix_t *matrix_strassen_compute_m6(matrix_t *a1, matrix_t *a3, matrix_t *b1,
                                     matrix_t *b2)
{
	matrix_t *sub_a3_a1 = matrix_math_subtract_matrices(a3, a1);
	matrix_t *add_b1_b2 = matrix_math_add_matrices(b1, b2);
	matrix_t *m6 = matrix_strassen_multiply_pot_matrices(sub_a3_a1, add_b1_b2);
	matrix_delete(add_b1_b2);
	matrix_delete(sub_a3_a1);

    return m6;
}

matrix_t *matrix_strassen_compute_m7(matrix_t *a2, matrix_t *a4, matrix_t *b3,
                                     matrix_t *b4)
{
	matrix_t *sub_a2_a4 = matrix_math_subtract_matrices(a2, a4);
	matrix_t *add_b3_b4 = matrix_math_add_matrices(b3, b4);
	matrix_t *m7 = matrix_strassen_multiply_pot_matrices(sub_a2_a4, add_b3_b4);
	matrix_delete(add_b3_b4);
	matrix_delete(sub_a2_a4);

    return m7;
}

matrix_t *matrix_strassen_compute_c1(matrix_t *m1, matrix_t *m4, matrix_t *m5,
                                     matrix_t *m7)
{
	matrix_t *pre_c1_1 = matrix_math_add_matrices(m1, m4);
	matrix_t *pre_c1_2 = matrix_math_subtract_matrices(pre_c1_1, m5);
	matrix_t *c1 = matrix_math_add_matrices(pre_c1_2, m7);
	matrix_delete(pre_c1_2);
	matrix_delete(pre_c1_1);

    return c1;
}

matrix_t *matrix_strassen_compute_c2(matrix_t *m3, matrix_t *m5)
{
	matrix_t *c2 = matrix_math_add_matrices(m3, m5);

    return c2;
}

matrix_t *matrix_strassen_compute_c3(matrix_t *m2, matrix_t *m4)
{
	matrix_t *c3 = matrix_math_add_matrices(m2, m4);

    return c3;
}

matrix_t *matrix_strassen_compute_c4(matrix_t *m1, matrix_t *m2, matrix_t *m3,
                                     matrix_t *m6)
{
	matrix_t *pre_c4_1 = matrix_math_subtract_matrices(m1, m2);
	matrix_t *pre_c4_2 = matrix_math_add_matrices(pre_c4_1, m3);
	matrix_t *c4 = matrix_math_add_matrices(pre_c4_2, m6);
	matrix_delete(pre_c4_2);
	matrix_delete(pre_c4_1);

    return c4;
}
