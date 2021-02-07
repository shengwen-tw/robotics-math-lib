#include <stdio.h>
#include <stdlib.h>
#include "robotics_math.h"

matrix_t* matrix_new(int r, int c)
{
	matrix_t *mat = (matrix_t *)malloc(sizeof(matrix_t));

	mat->row = r;
	mat->column = c;
	mat->data = (float *)malloc(sizeof(float) * r * c);

	return mat;
}

void matrix_delete(matrix_t *mat)
{
	if(mat->data != NULL) free(mat->data);
	if(mat != NULL) free(mat);
}

void print_matrix(char *prompt, matrix_t *mat)
{
	printf("%s (%dx%d) = \n", prompt, mat->row, mat->column);

	int r, c;
	for(r = 0; r < mat->row; r++) {
		printf("   ");
		for(c = 0; c < mat->column; c++) {
			printf("%f  ", mat->data[r * mat->column + c]);
		}
		printf("\n");
	}
}
