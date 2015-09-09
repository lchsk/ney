CXXFLAGS = -fopenmp -O3 -Ofast -opt-assume-safe-padding -fno-alias
NVCCFLAGS = -Xcompiler "-fopenmp"
NVCC = nvcc

EXAMPLES = saxpy_cpu saxpy_gpu saxpy_mic \
reduce_cpu reduce_gpu reduce_mic


all : $(EXAMPLES)

clean :
	rm -f $(EXAMPLES) *.o *.out

saxpy_cpu :
	$(CXX) saxpy.cpp $(CXXFLAGS) -o saxpy_cpu

saxpy_gpu :
	$(NVCC) saxpy.cu $(NVCCFLAGS) -o saxpy_gpu

saxpy_mic :
	$(CXX) saxpy.cpp $(CXXFLAGS) -mmic -o saxpy_mic

reduce_cpu :
	$(CXX) reduce.cpp $(CXXFLAGS) -o reduce_cpu

reduce_gpu :
	$(NVCC) reduce.cu $(NVCCFLAGS) -o reduce_gpu

reduce_mic :
	$(CXX) reduce.cpp $(CXXFLAGS) -mmic -o reduce_mic
