unit_test_matrix:
	@$(MAKE) -C ./unit_test/matrix -f Makefile
	@python3 ./unit_test/matrix/matrix_test.py

clean:
	@$(MAKE) -C ./unit_test/matrix -f Makefile clean

.PHONY: unit_test_matrix clean
