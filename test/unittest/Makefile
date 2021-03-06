GTEST_DIR = ../../thirdparty/googletest

USER_DIR = .

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

CPP_TEST_FLAGS = -pthread -fopenmp

COVERAGE =
REPORT =
REPORT_CODE =

ifeq ($(CXX), g++)
    COVERAGE = --coverage
endif

ifeq ($(DEBUG), 1)
	ifeq ($(CXX), icpc)
		REPORT = -vec-report6
		REPORT_CODE = -DUSE_MIC=FALSE
	endif
endif

TESTS = vector_unittest basic_unittest advanced_unittest apply_unittest other_unittest sort_unittest io_unittest condition_unittest offloading_unittest

TESTS_MIC = vector_unittest_mic basic_unittest_mic advanced_unittest_mic apply_unittest_mic other_unittest_mic sort_unittest_mic io_unittest_mic condition_unittest_mic offloading_unittest_mic

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

all : gtest.a $(TESTS)

clean :
	rm -f $(TESTS) $(TESTS_MIC) gtest.a gtest_main.a *.o
	rm -f *_report
	rm -f *.optrpt
	rm -f *.gcno
	rm -f *.gcda

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
	vector_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o vector_unittest 2> vector_unittest_report

basic_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	basic_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o basic_unittest 2> basic_unittest_report

advanced_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	advanced_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o advanced_unittest 2> advanced_unittest_report

apply_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	apply_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o apply_unittest 2> apply_unittest_report

other_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	other_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o other_unittest 2> other_unittest_report

sort_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	sort_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o sort_unittest 2> sort_unittest_report

io_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	io_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o io_unittest 2> io_unittest_report

condition_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	condition_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o condition_unittest 2> condition_unittest_report

offloading_unittest :
	$(CXX) -I $(GTEST_DIR)/include/ \
	offloading_unittest.cpp gtest.a $(CPP_TEST_FLAGS) $(COVERAGE) $(REPORT) $(REPORT_CODE) -o offloading_unittest 2> offloading_unittest_report
