#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "robotics_math.h"
#include "matrix.h"

void matrix_init(matrix_t *mat, int r, int c, float *mat_data)
{
	mat->data = mat_data;
	mat->row = r;
	mat->column = c;
}

void matrix_set_zeros(matrix_t *mat)
{
	ASSERT(mat->data != NULL);

	uint32_t cnt = mat->row * mat->column;
	float *curr_element = mat->data;

	while(cnt--) {
		*curr_element++ = 0;
	}
}

void matrix_set_identity(matrix_t *mat)
{
	ASSERT(mat->data != NULL);
	ASSERT(mat->row == mat->column);

	uint32_t row_num    = mat->row;
	uint32_t column_num = mat->column;

	int32_t upper_num, lower_num;

	float *data_ptr = mat->data;

	int r, c;
	for(r = 0; r < mat->row; r++) {
		/* initialize lower triangle to 0 */
		lower_num = r;
		while(lower_num > 0) {
			*data_ptr++ = 0;
			lower_num--;
		}

		/* initialize diagonal to 1*/
		*data_ptr++ = 1;

		/* initialize upper triangle to 0 */
		upper_num = row_num - r - 1; //minus 1 is for diagonal
		while(upper_num > 0) {
			*data_ptr++ = 0;
			upper_num--;
		}
	}
}

void matrix_add(matrix_t *mat1, matrix_t *mat2, matrix_t *mat_result)
{
	ASSERT(mat1->data != NULL);
	ASSERT(mat2->data != NULL);
	ASSERT(mat_result->data != NULL);

	ASSERT(mat1->row == mat2->row);
	ASSERT(mat1->column == mat2->column);

	ASSERT(mat_result->row == mat1->row);
	ASSERT(mat_result->column == mat1->column);

	int r, c;
	for(r = 0; r < mat1->row; r++) {
		for(c = 0; c < mat1->column; c++) {
			matrix_at(mat_result, r, c) = matrix_at(mat1, r, c) + matrix_at(mat2, r, c);
		}
	}
}

void matrix_sub(matrix_t *mat1, matrix_t *mat2, matrix_t *mat_result)
{
	ASSERT(mat1->data != NULL);
	ASSERT(mat2->data != NULL);
	ASSERT(mat_result->data != NULL);

	ASSERT(mat1->row == mat2->row);
	ASSERT(mat1->column == mat2->column);

	ASSERT(mat_result->row == mat1->row);
	ASSERT(mat_result->column == mat1->column);

	int r, c;
	for(r = 0; r < mat1->row; r++) {
		for(c = 0; c < mat1->column; c++) {
			matrix_at(mat_result, r, c) = matrix_at(mat1, r, c) - matrix_at(mat2, r, c);
		}
	}
}

void matrix_multiply(matrix_t *mat1, matrix_t *mat2, matrix_t *mat_result)
{
	ASSERT(mat1->data != NULL);
	ASSERT(mat2->data != NULL);
	ASSERT(mat_result->data != NULL);

	ASSERT(mat_result->row == mat1->row);
	ASSERT(mat_result->column == mat2->column);

	matrix_set_zeros(mat_result); //XXX: this code could be further optimized

	/* cache awared naive multiplication */
	int i, j, k;
	for(i = 0; i < mat1->row; i++) {
		for(k = 0; k < mat1->column; k++) {
			for(j = 0; j < mat2->column; j++) {
				matrix_at(mat_result, i, k) += 
					matrix_at(mat1, i, j) * matrix_at(mat2, j, k);
			}
		}
	}
}

void matrix_scaling(double scaler, matrix_t *mat, matrix_t *mat_scaled)
{
	ASSERT(mat->data != NULL);
	ASSERT(mat_scaled->data != NULL);

	ASSERT(mat->row == mat_scaled->row);
	ASSERT(mat->column == mat_scaled->column);

	int r, c;
	for(r = 0; r < mat->row; r++) {
		for(c = 0; c < mat->column; c++) {
			matrix_at(mat_scaled, r, c) = scaler * matrix_at(mat, r, c);
		}
	}
}

void matrix_transpose(matrix_t *mat, matrix_t *mat_transposed)
{
	ASSERT(mat->data != NULL);
	ASSERT(mat_transposed->data != NULL);

	ASSERT(mat->row == mat_transposed->column);
	ASSERT(mat->column == mat_transposed->row);

	int r, c;
	for(r = 0; r < mat->row; r++) {
		for(c = 0; c < mat->column; c++) {
			matrix_at(mat_transposed, c, r) = matrix_at(mat, r,  c);
		}
	}
}

bool matrix_inverse(matrix_t *mat, matrix_t *mat_inv)
{
	ASSERT(mat->data != NULL);
	ASSERT(mat_inv->data != NULL);

	ASSERT(mat->row == mat->column);
	ASSERT(mat->row == mat_inv->row);
	ASSERT(mat->column == mat_inv->column);

	uint32_t row_num    = mat->row;
	uint32_t column_num = mat->column;

	/*================================================*
	 * initialize return matrix "mat_inv" to identity *
	 *================================================*/
	uint32_t r, c;
	uint32_t i, j;
	uint32_t upper_num, lower_num;
	float *data_ptr;
	float *inv_data_ptr = mat_inv->data;

	for(r = 0; r < mat_inv->row; r++) {
		/* initialize lower triangle to 0 */
		lower_num = r;
		while(lower_num > 0) {
			*inv_data_ptr++ = 0;
			lower_num--;
		}

		/* initialize diagonal to 1*/
		*inv_data_ptr++ = 1;

		/* initialize upper triangle to 0 */
		upper_num = row_num - r - 1; //minus 1 is for diagonal
		while(upper_num > 0) {
			*inv_data_ptr++ = 0;
			upper_num--;
		}
	}

	/*=====================*
	 * Gauss-Jordan method *
	 *=====================*/
	data_ptr = mat->data;
	float max_val = 0;
	uint32_t max_row_pos;

	for(c = 0; c < mat->column; c++) {
		/* select the element with largest absolute value as pivot and
		 * put it on the diagonal */
		for(r = 0; r < mat->row; r++) {
		        if(*data_ptr > 0) {
		                if(*data_ptr > max_val) {
		                        max_val = *data_ptr;
					max_row_pos = r;
	        	        }
		        } else {
		                if(-*data_ptr > max_val) {
		                        max_val = *data_ptr;
					max_row_pos = r;
		                }
		        }

			//next row
			data_ptr += column_num;
		}

		/* pivot not found (the whole column is zero), the matrix is singular */
		if(max_val == 0.0f) {
			return false; //singular matrix
		}

		/* significant value is not on the diagonal */
		if(c != max_row_pos) {
			/* row swapping */
			float *left_old = &mat->data[c * column_num + c];
			float *left_swap = &mat->data[max_row_pos * column_num + c];
			float *right_old = &mat_inv->data[c * column_num + c];
			float *right_swap = &mat_inv->data[max_row_pos * column_num + c]; 

			float tmp;
			for(i = c; i < column_num; i++) {
				//swap original matrix
				tmp = *left_old;
				*left_old = *left_swap;
				*left_swap = tmp;

				//swap augmented matrix
				tmp = *right_old;
				*right_old = *right_swap;
				*right_swap = tmp;

				/* next element */
				left_old++;
				left_swap++;
				right_old++;
				right_swap++;
			}
		}

		/* divide pivot row by pivot value */
		data_ptr = &mat->data[c * column_num + c];
		inv_data_ptr = &mat_inv->data[c * column_num + c];
		float pivot_value = *data_ptr;
		for(i = 0; i < column_num; i++) {
			*data_ptr++ /= pivot_value;
			*inv_data_ptr ++ /= pivot_value;
		}

		/* perform row elimination */
		float *left_eliminate_row = &mat->data[(max_row_pos * column_num) + c];
		float *right_eliminate_row = &mat_inv->data[(max_row_pos * column_num) + c];
		for(i = 0; i < row_num; i++) {
			if(i == c) {
				continue;
			}

			float row_operation_scaler = *left_eliminate_row;
			for(j = c; j < column_num; j++) {
				/* row elimination */
				*left_eliminate_row -= row_operation_scaler * data_ptr[j];
				*right_eliminate_row -= row_operation_scaler * inv_data_ptr[j];

				/* next element */
				left_eliminate_row++;
				right_eliminate_row++;
				data_ptr++;
				inv_data_ptr++;
			}
		}
	}
}
