CXXFLAGS = -fopenmp

EXAMPLES = bitonic_sort charcount_vector wordcount saxpy weld_triangles run_length_encoding pi_estimation image_effects particles

all : $(EXAMPLES)

clean :
	rm -f $(EXAMPLES) *.o *.out
	rm -f data/cat_*bmp

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

run_length_encoding :
	$(CXX) run_length_encoding.cpp $(CXXFLAGS) -o run_length_encoding

pi_estimation :
	$(CXX) pi_estimation.cpp $(CXXFLAGS) -o pi_estimation

image_effects :
	$(CXX) image_effects.cpp $(CXXFLAGS) -o image_effects

particles :
	$(CXX) particles.cpp $(CXXFLAGS) -o particles
