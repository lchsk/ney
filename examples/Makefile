CXXFLAGS = -fopenmp

EXAMPLES = bitonic_sort charcount_vector wordcount

all : $(EXAMPLES)

clean :
	rm -f $(EXAMPLES) *.o *.out

bitonic_sort :
	$(CXX) bitonic.cpp $(CXXFLAGS) -o bitonic_sort

charcount_vector :
	$(CXX) charcount.cpp $(CXXFLAGS) -o charcount_vector

wordcount :
	$(CXX) wordcount.cpp $(CXXFLAGS) -o wordcount
