#include <stdio.h>
#include "robotics_math.h"

void matrix_test_init(void)
{
	float mat_a_data[] = {1, 2, 3,
                              4, 5, 6,
                              7, 8, 9};

	matrix_t mat_a;
	matrix_init(&mat_a, 3, 3, mat_a_data);

	printf("matrix_init:\n\r");
	print_matrix("mat_a", &mat_a);
	printf("----------------------------------\n");
}

void matrix_test_set_zeros(void)
{
	float mat_a_data[] = {1, 2, 3,
                              4, 5, 6,
                              7, 8, 9};

	matrix_t mat_a;
	matrix_init(&mat_a, 3, 3, mat_a_data);
	matrix_set_zeros(&mat_a);

	printf("matrix_set_zeros:\n\r");
	print_matrix("mat_a", &mat_a);
	printf("----------------------------------\n");
}

void matrix_test_set_identity(void)
{
	float mat_a_data[] = {1, 2, 3,
                              4, 5, 6,
                              7, 8, 9};

	matrix_t mat_a;
	matrix_init(&mat_a, 3, 3, mat_a_data);
	matrix_set_identity(&mat_a);

	printf("matrix_set_identity:\n\r");
	print_matrix("mat_a", &mat_a);
	printf("----------------------------------\n");
}

void matrix_test_add(void)
{
	float mat_a_data[] = {1, 2, 3,
                              4, 5, 6,
                              7, 8, 9};
	matrix_t mat_a;
	matrix_init(&mat_a, 3, 3, mat_a_data);

	float mat_b_data[] = {  10,   10,   10,
                                 5,    5,    5,
                              1000, 1000, 1000};
	matrix_t mat_b;
	matrix_init(&mat_b, 3, 3, mat_b_data);

	float mat_result_data[3 * 3];
	matrix_t mat_result;
	matrix_init(&mat_result, 3, 3, mat_result_data);

	matrix_add(&mat_a, &mat_b, &mat_result);

	printf("matrix_add:\n\r");
	print_matrix("mat_a", &mat_a);
	print_matrix("mat_b", &mat_b);
	print_matrix("mat_result", &mat_result);
	printf("----------------------------------\n");
}

void matrix_test_sub(void)
{
	float mat_a_data[] = {1, 2, 3,
                              4, 5, 6,
                              7, 8, 9};
	matrix_t mat_a;
	matrix_init(&mat_a, 3, 3, mat_a_data);

	float mat_b_data[] = {  10,   10,   10,
                                 5,    5,    5,
                              1000, 1000, 1000};
	matrix_t mat_b;
	matrix_init(&mat_b, 3, 3, mat_b_data);

	float mat_result_data[3 * 3];
	matrix_t mat_result;
	matrix_init(&mat_result, 3, 3, mat_result_data);

	matrix_sub(&mat_a, &mat_b, &mat_result);

	printf("matrix_sub:\n\r");
	print_matrix("mat_a", &mat_a);
	print_matrix("mat_b", &mat_b);
	print_matrix("mat_result", &mat_result);
	printf("----------------------------------\n");
}

void matrix_test_multiply(void)
{
	float mat_a_data[] = {1, 2, 3,
                              4, 5, 6,
                              7, 8, 9};
	matrix_t mat_a;
	matrix_init(&mat_a, 3, 3, mat_a_data);

	float mat_b_data[] = {  10,   10,   10,
                                 5,    5,    5,
                              1000, 1000, 1000};
	matrix_t mat_b;
	matrix_init(&mat_b, 3, 3, mat_b_data);

	float mat_result_data[3 * 3];
	matrix_t mat_result;
	matrix_init(&mat_result, 3, 3, mat_result_data);

	matrix_multiply(&mat_a, &mat_b, &mat_result);

	printf("matrix_sub:\n\r");
	print_matrix("mat_a", &mat_a);
	print_matrix("mat_b", &mat_b);
	print_matrix("mat_result", &mat_result);
	printf("----------------------------------\n");
}

int main(void)
{
	matrix_test_init();
	matrix_test_set_zeros();
	matrix_test_set_identity();
	matrix_test_add();
	matrix_test_sub();
	matrix_test_multiply();

	return 0;
}
