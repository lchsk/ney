CXXFLAGS = -fopenmp -O3
NVCCFLAGS = -Xcompiler "-fopenmp"
NVCC = nvcc

EXAMPLES = saxpy_cpu saxpy_gpu


all : $(EXAMPLES)

clean :
	rm -f $(EXAMPLES) *.o *.out

saxpy_cpu :
	$(CXX) saxpy.cpp $(CXXFLAGS) -o saxpy_cpu

saxpy_gpu :
	$(NVCC) saxpy.cu $(NVCCFLAGS) -o saxpy_gpu
