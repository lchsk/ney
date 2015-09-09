CXXFLAGS = -fopenmp
NVCC = nvcc

EXAMPLES = saxpy

all : $(EXAMPLES)

clean :
	rm -f $(EXAMPLES) *.o *.out
	rm -f data/cat_*bmp

saxpy :
	# $(CXX) saxpy.cpp $(CXXFLAGS) -o saxpy
	$(NVCC) -o saxpy saxpy.cu -Xcompiler "-fopenmp"
