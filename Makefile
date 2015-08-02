
INCLUDE_DIR = ./include/ney
TEST_DIR = ./test/unittest

# HEADERS = $(INCLUDE_DIR)/*.hpp
# FILES = $(INCLUDE_DIR)/detail/*.inl
# FILES = $(INCLUDE_DIR)/main.hpp $(INCLUDE_DIR)/fill.hpp $(INCLUDE_DIR)/detail/fill.inl
# $(INCLUDE_DIR)/new_vector.hpp $(INCLUDE_DIR)/operation.hpp \
# $(INCLUDE_DIR)/random.hpp $(INCLUDE_DIR)/status.hpp \
# $(INCLUDE_DIR)/vector.hpp



all:
	cd $(TEST_DIR) && $(MAKE)
	# $(CXX) ./experiments/test.cpp -fopenmp

tests:
	cd $(TEST_DIR) && ./run_tests.sh

coverage:
	lcov --capture --directory ./test/unittest --output-file coverage.info
	genhtml coverage.info --output-directory out

docs:
	doxygen doc/conf

clean:
	rm -rf out
	cd $(TEST_DIR) && $(MAKE) clean
	
	rm -rf $(INCLUDE_DIR)/*.gch
	rm -rf test/unittest/*.gcda
	rm -rf test/unittest/*.gcno

	rm -rf doc/html

	rm -f coverage.info
