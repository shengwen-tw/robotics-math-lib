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

int main(void)
{
	matrix_test_init();
	matrix_test_set_zeros();
	matrix_test_set_identity();

	return 0;
}
