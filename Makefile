INCLUDE_DIR = ./include/ney
TEST_DIR = ./test/unittest
REPORT_DIR = ./test/report
EXAMPLES_DIR = ./examples

all:
	cd $(TEST_DIR) && $(MAKE)

tests:
	cd $(TEST_DIR) && ./run_tests.sh

coverage:
	sudo apt-cache madison lcov
	lcov --capture --directory ./test/unittest --output-file coverage.info
	genhtml coverage.info --output-directory out

example:
	cd $(EXAMPLES_DIR) && $(MAKE)

build_reports:
	cd $(REPORT_DIR) && ./build.sh

run_reports:
	cd  $(REPORT_DIR) && python tester.py

docs:
	doxygen doc/conf

clean:
	rm -rf out
	cd $(TEST_DIR) && $(MAKE) clean
	cd $(EXAMPLES_DIR) && $(MAKE) clean

	rm -rf $(INCLUDE_DIR)/*.gch

	rm -rf doc/html

	rm -f coverage.info
