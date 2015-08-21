CXXFLAGS = -fopenmp

EXAMPLES = bitonic_sort charcount_vector wordcount saxpy weld_triangles

all : $(EXAMPLES)

clean :
	rm -f $(EXAMPLES) *.o *.out

bitonic_sort :
	$(CXX) bitonic.cpp $(CXXFLAGS) -o bitonic_sort

charcount_vector :
	$(CXX) charcount.cpp $(CXXFLAGS) -o charcount_vector

wordcount :
	$(CXX) wordcount.cpp $(CXXFLAGS) -o wordcount

saxpy :
	$(CXX) saxpy.cpp $(CXXFLAGS) -o saxpy

weld_triangles :
	$(CXX) weld_triangles.cpp $(CXXFLAGS) -o weld_triangles
