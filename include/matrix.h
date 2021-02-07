#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdint.h>
#include <stdbool.h>

#define matrix_at(mat_ptr, r, c) (mat_ptr)->data[((r) * (mat_ptr)->column) + (c)]

typedef struct {
	int row;
	int column;
	float *data;
} matrix_t;

void matrix_init(matrix_t *mat, int r, int c, float *mat_data);
void matrix_set_zeros(matrix_t *mat);
void matrix_set_identity(matrix_t *mat);
void matrix_add(matrix_t *mat1, matrix_t *mat2, matrix_t *mat_result);
void matrix_sub(matrix_t *mat1, matrix_t *mat2, matrix_t *mat_result);
void matrix_multiply(matrix_t *mat1, matrix_t *mat2, matrix_t *mat_result);
void matrix_scaling(double scaler, matrix_t *mat, matrix_t *mat_scaled);
void matrix_transpose(matrix_t *mat, matrix_t *mat_transposed);
bool matrix_inverse(matrix_t *mat, matrix_t *mat_inv);

#endif
