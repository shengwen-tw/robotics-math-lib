#ifndef __MATRIX_H__
#define __MATRIX_H__

#define matrix_at(mat_ptr, r, c) (mat_ptr)->data[((r) * (mat_ptr)->column) + (c)]

typedef struct {
	int row;
	int column;
	float *data;
} matrix_t;

#endif
