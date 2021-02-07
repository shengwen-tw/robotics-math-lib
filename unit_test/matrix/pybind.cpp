#include <iostream>
#include <sys/time.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "robotics_math.h"

using namespace std;
namespace py = pybind11;

using pyarray = std::optional<py::array_t<float>>;

bool unit_test_debug_print = false;

void test_print_matrix(string prompt, matrix_t *mat)
{
	if(unit_test_debug_print == false) {
		return;
	}

	printf("%s (%dx%d) = \n", prompt.c_str(), mat->row, mat->column);

	int r, c;
	for(r = 0; r < mat->row; r++) {
		printf("   ");
		for(c = 0; c < mat->column; c++) {
			printf("%f  ", mat->data[r * mat->column + c]);
		}
		printf("\n");
	}
}

bool convert_np_array_to_matrix(matrix_t **mat, pyarray &py_arr)
{
	/* use C++17 std::optional to identify if python object exists (!= None) */
	if(py_arr.has_value() == false) {
		return false;
	}

	*mat = matrix_new((int)py_arr.value().shape(0), (int)py_arr.value().shape(1));

	auto data = py_arr.value().unchecked<2>();
	for (py::ssize_t i = 0; i < data.shape(0); i++) {
		for (py::ssize_t j = 0; j < data.shape(1); j++) {
			matrix_at(*mat, i, j) = data(i, j);
		}
	}

	return true;
}

py::array_t<float> convert_np_array_to_matrix(matrix_t *mat)
{
	unsigned long n_row = mat->row;
	unsigned long n_column = mat->column;

	auto buf_info =
	        py::buffer_info(mat->data,
	                        sizeof(float),
	                        py::format_descriptor<float>::format(),
	                        2,
	                        std::vector<size_t> {n_row, n_column},
	                        std::vector<size_t> {n_column * sizeof(float), sizeof(float)}
	                       );
	return py::array_t<float>(buf_info);
}

pyarray my_matrix_inverse(pyarray mat_np)
{
	matrix_t *mat;
	convert_np_array_to_matrix(&mat, mat_np);

	matrix_t *mat_inv = matrix_new(mat->row, mat->column);

	matrix_inverse(mat, mat_inv);

	pyarray result = convert_np_array_to_matrix(mat_inv);

	matrix_delete(mat);
	matrix_delete(mat_inv);

	return result;
}

pyarray my_matrix_add(pyarray mat1_np, pyarray mat2_np)
{
	matrix_t *mat1, *mat2;
	convert_np_array_to_matrix(&mat1, mat1_np);
	convert_np_array_to_matrix(&mat2, mat2_np);

	matrix_t *mat_result = matrix_new(mat1->row, mat1->column);

	matrix_add(mat1, mat2, mat_result);

	pyarray result = convert_np_array_to_matrix(mat_result);

	matrix_delete(mat1);
	matrix_delete(mat2);
	matrix_delete(mat_result);

	return result;
}

pyarray my_matrix_sub(pyarray mat1_np, pyarray mat2_np)
{
	matrix_t *mat1, *mat2, *mat_result;

	convert_np_array_to_matrix(&mat1, mat1_np);
	convert_np_array_to_matrix(&mat2, mat2_np);
	mat_result = matrix_new(mat1->row, mat1->column);

	matrix_sub(mat1, mat2, mat_result);

	pyarray result = convert_np_array_to_matrix(mat_result);

	matrix_delete(mat1);
	matrix_delete(mat2);
	matrix_delete(mat_result);

	return result;
}

pyarray my_matrix_multiply(pyarray mat1_np, pyarray mat2_np)
{
	matrix_t *mat1, *mat2, *mat_result;

	convert_np_array_to_matrix(&mat1, mat1_np);
	convert_np_array_to_matrix(&mat2, mat2_np);
	mat_result = matrix_new(mat1->row, mat2->column);

	matrix_multiply(mat1, mat2, mat_result);

	pyarray result = convert_np_array_to_matrix(mat_result);

	matrix_delete(mat1);
	matrix_delete(mat2);
	matrix_delete(mat_result);

	return result;
}

pyarray my_matrix_scaling(float scaler, pyarray in_np)
{
	matrix_t *in, *out;

	convert_np_array_to_matrix(&in, in_np);
	out = matrix_new(in->row, in->column);

	matrix_scaling(scaler, in, out);

	pyarray result = convert_np_array_to_matrix(out);

	matrix_delete(in);
	matrix_delete(out);

	return result;
}

pyarray my_matrix_transpose(pyarray mat_np)
{
	matrix_t *mat, *trans_mat;

	convert_np_array_to_matrix(&mat, mat_np);
	trans_mat = matrix_new(mat->column, mat->row);

	matrix_transpose(mat, trans_mat);

	pyarray result = convert_np_array_to_matrix(trans_mat);

	matrix_delete(mat);
	matrix_delete(trans_mat);

	return result;
}

PYBIND11_MODULE(matrix_wrapper, mod)
{
	mod.doc() = "unit test wrapper for robotics-math-lib";
	mod.def("matrix_inverse", &my_matrix_inverse, "");
	mod.def("matrix_add", &my_matrix_add, "");
	mod.def("matrix_sub", &my_matrix_sub, "");
	mod.def("matrix_multiply", &my_matrix_multiply, "");
	mod.def("matrix_scaling", &my_matrix_scaling, "");
	mod.def("matrix_transpose", &my_matrix_transpose, "");
}
