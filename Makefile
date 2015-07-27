
INCLUDE_DIR = ./include/ney

HEADERS = $(INCLUDE_DIR)/*.hpp
FILES = $(INCLUDE_DIR)/detail/*.inl
# FILES = $(INCLUDE_DIR)/main.hpp $(INCLUDE_DIR)/fill.hpp $(INCLUDE_DIR)/detail/fill.inl
# $(INCLUDE_DIR)/new_vector.hpp $(INCLUDE_DIR)/operation.hpp \
# $(INCLUDE_DIR)/random.hpp $(INCLUDE_DIR)/status.hpp \
# $(INCLUDE_DIR)/vector.hpp



all:
	cd ./test/unittest && $(MAKE)
	# $(CXX) ./experiments/test.cpp -fopenmp

test:
	all

clean:
	cd ./test/unittest && $(MAKE) clean
