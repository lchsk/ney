GTEST_DIR = ../../thirdparty/googletest

USER_DIR = .

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

CPP_TEST_FLAGS = -pthread -fopenmp

COVERAGE =
REPORT =
DEBUG = 0

ifeq ($(CXX), g++)
    COVERAGE = --coverage
endif

ifeq ($(DEBUG), 1)
	ifeq ($(CXX), icpc)
		REPORT = -vec-report6
	endif
endif

TESTS = vector_unittest basic_unittest advanced_unittest apply_unittest other_unittest sort_unittest io_unittest condition_unittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : gtest.a $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o
	rm -f *_report
	rm -f *.optrpt
	rm -f *.gcno

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

vector_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	vector_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o vector_unittest 2> vector_unittest_report

basic_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	basic_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o basic_unittest 2> basic_unittest_report

advanced_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	advanced_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o advanced_unittest 2> advanced_unittest_report

apply_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	apply_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o apply_unittest 2> apply_unittest_report

other_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	other_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o other_unittest 2> other_unittest_report

sort_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	sort_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o sort_unittest 2> sort_unittest_report

io_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	io_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o io_unittest 2> io_unittest_report

condition_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	condition_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) -o condition_unittest 2> condition_unittest_report
