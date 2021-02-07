unit_test_matrix:
	@$(MAKE) -C ./unit_test/matrix -f Makefile
	@python3 ./unit_test/matrix/matrix_test.py

.PHONY: unit_test_matrix
