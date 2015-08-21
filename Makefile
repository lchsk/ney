INCLUDE_DIR = ./include/ney
TEST_DIR = ./test/unittest
EXAMPLES_DIR = ./examples

all:
	cd $(TEST_DIR) && $(MAKE)

tests:
	cd $(TEST_DIR) && ./run_tests.sh

coverage:
	lcov --capture --directory ./test/unittest --output-file coverage.info
	genhtml coverage.info --output-directory out

example:
	cd $(EXAMPLES_DIR) && $(MAKE)

docs:
	doxygen doc/conf

clean:
	rm -rf out
	cd $(TEST_DIR) && $(MAKE) clean
	cd $(EXAMPLES_DIR) && $(MAKE) clean

	rm -rf $(INCLUDE_DIR)/*.gch
	rm -rf test/unittest/*.gcda
	rm -rf test/unittest/*.gcno

	rm -rf doc/html

	rm -f coverage.info
