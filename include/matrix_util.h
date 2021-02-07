#ifndef __MATRIX_UTIL_H__
#define __MATRIX_UTIL_H__

matrix_t* matrix_new(int r, int c);
void matrix_delete(matrix_t *mat);
void print_matrix(char *prompt, matrix_t *mat);

#endif
