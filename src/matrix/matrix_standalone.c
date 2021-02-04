#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "robotics_math.h"
#include "matrix.h"

void matrix_init(matrix_t *mat, float *mat_data, int r, int c)
{
	mat->data = mat_data;
	mat->row = r;
	mat->column = c;
	memset(mat, 0, sizeof(float) * r * c);
}

void matrix_add(matrix_t *mat1, matrix_t *mat2, matrix_t *mat_result)
{
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
	ASSERT(mat_result->row == mat1->row);
	ASSERT(mat_result->column == mat2->column);

	/* cache awared naive multiplication */
	int i, j, k;
	for(i = 0; i < mat1->row; i++) {
		for(k = 0; k < mat1->column; k++) {
			for(j = 0; j < mat2->column; j++) {
				matrix_at(mat_result, i, j) += 
					matrix_at(mat1, i, k) * matrix_at(mat2, k, j);
			}
		}
	}
}

void matrix_scaling(double scaler, matrix_t *mat, matrix_t *mat_scaled)
{
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

	uint32_t last_of_curr_row;
	for(r = 0; r < mat_inv->row; r++) {
		/* initialize lower triangle */
		upper_num = row_num - r;
		while(upper_num > 0) {
			*inv_data_ptr++ = 0; //set value and move to next
			upper_num--;	
		}

		/* initialize diagonal */
		*inv_data_ptr++ = 1; //set value 1 and move to next

		/* initialize upper triangle */
		lower_num = r - 1;
		while(lower_num > 0) {
			*inv_data_ptr++ = 0; //set value and move to next
			lower_num--;
		}
	}

	/*=====================*
	 * Gauss-Jordan method *
	 *=====================*/
	data_ptr = mat->data;
	float max_val = 0;
	uint32_t max_row_pos;

	for(c = 0; c < mat->column; c++) {
		/* for a fixed column, find the largest value of all rows, and let
		 * it become the pivot element by putting it on the diagonal */
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

			//move the data pointer to next row
			data_ptr += column_num;
		}

		/* pivot not found, the matrix is singular */
		if(max_val == 0.0f) {
			return false; //singular matrix
		}

		/* significant value is not on the diagonal */
		if(c != max_row_pos) {
			/* row swapping */
			float *left_old = &mat->data[c * column_num];
			float *left_swap = &mat->data[max_row_pos * column_num];
			float *right_old = &mat_inv->data[c * column_num];
			float *right_swap = &mat_inv->data[max_row_pos * column_num]; 

			float tmp;
			for(i = 0; i < column_num; i++) {
				//swap original matrix
				tmp = *left_old;
				*left_old = *left_swap;
				*left_swap = tmp;

				//swap augmented matrix
				tmp = *right_old;
				*right_old = *right_swap;
				*right_swap = tmp;

				left_old++;
				left_swap++;
				right_old++;
				right_swap++;
			}
		}

		/*==========================*
		 * Gauss-Jordan elimination *
		 *==========================*/
		
		/* divide pivot row by pivot value */
		float pivot_value = *data_ptr;
		for(i = 0; i < column_num; i++) {
			*data_ptr++ /= pivot_value;
			*inv_data_ptr ++ /= pivot_value;
		}

		/* perform row opertation */
		float *left_eliminate_row;
		float *right_eliminate_row;
		for(i = 0; i < row_num; i++) {
			if(i == c) {
				continue;
			}

			float row_operation_scaler;
			for(j = 0; j < column_num; j++) {
				*left_eliminate_row++ -= row_operation_scaler * data_ptr[j];
				*right_eliminate_row++ -= row_operation_scaler * inv_data_ptr[j];
			}
		}
	}
}
