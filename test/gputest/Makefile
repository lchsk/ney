GTEST_DIR = ../../thirdparty/googletest

CC_CUDA = nvcc

USER_DIR = .

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

CPP_TEST_FLAGS = -pthread -fopenmp

COVERAGE =
REPORT =
REPORT_CODE =

TESTS = advanced_unittest basic_unittest sort_unittest io_unittest vector_unittest apply_unittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : gtest.a $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o
	rm -f *_report
	rm -f *.optrpt
	rm -f *.gcno
	rm -f *.gcda

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

advanced_unittest :
	$(CC_CUDA) -I $(GTEST_DIR)/include/ \
	advanced_unittest.cu gtest.a -Xcompiler "$(CPP_TEST_FLAGS)" $(COVERAGE) $(REPORT) $(REPORT_CODE) -o advanced_unittest 2> advanced_unittest_report

basic_unittest :
	$(CC_CUDA) -I $(GTEST_DIR)/include/ \
	basic_unittest.cu gtest.a -Xcompiler "$(CPP_TEST_FLAGS)" $(COVERAGE) $(REPORT) $(REPORT_CODE) -o basic_unittest 2> basic_unittest_report

sort_unittest :
	$(CC_CUDA) -I $(GTEST_DIR)/include/ \
	sort_unittest.cu gtest.a -Xcompiler "$(CPP_TEST_FLAGS)" $(COVERAGE) $(REPORT) $(REPORT_CODE) -o sort_unittest 2> sort_unittest_report

io_unittest :
	$(CC_CUDA) -I $(GTEST_DIR)/include/ \
	io_unittest.cu gtest.a -Xcompiler "$(CPP_TEST_FLAGS)" $(COVERAGE) $(REPORT) $(REPORT_CODE) -o io_unittest 2> io_unittest_report

vector_unittest :
	$(CC_CUDA) -I $(GTEST_DIR)/include/ \
	vector_unittest.cu gtest.a -Xcompiler "$(CPP_TEST_FLAGS)" $(COVERAGE) $(REPORT) $(REPORT_CODE) -o vector_unittest 2> vector_unittest_report

apply_unittest :
	$(CC_CUDA) -I $(GTEST_DIR)/include/ \
	apply_unittest.cu gtest.a -Xcompiler "$(CPP_TEST_FLAGS)" $(COVERAGE) $(REPORT) $(REPORT_CODE) -o apply_unittest 2> apply_unittest_report
