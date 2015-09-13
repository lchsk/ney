CXXFLAGS = -fopenmp -O3 -Ofast -opt-assume-safe-padding -fno-alias
NVCCFLAGS = -Xcompiler "-fopenmp -O3"
NVCC = nvcc

EXAMPLES = saxpy_cpu saxpy_gpu saxpy_mic \
functions_cpu functions_gpu functions_mic \
charcount_cpu charcount_gpu charcount_mic \
off_cpu


all : $(EXAMPLES)

clean :
	rm -f $(EXAMPLES) *.o *.out

saxpy_cpu :
	$(CXX) saxpy.cpp $(CXXFLAGS) -o saxpy_cpu

saxpy_gpu :
	$(NVCC) saxpy.cu $(NVCCFLAGS) -o saxpy_gpu

saxpy_mic :
	$(CXX) saxpy.cpp $(CXXFLAGS) -mmic -o saxpy_mic

off_cpu :
	$(CXX) off.cpp $(CXXFLAGS) -o off_cpu

charcount_cpu :
	$(CXX) charcount.cpp $(CXXFLAGS) -o charcount_cpu

charcount_gpu :
	$(NVCC) charcount.cu $(NVCCFLAGS) -o charcount_gpu

charcount_mic :
	$(CXX) charcount.cpp $(CXXFLAGS) -mmic -o charcount_mic

functions_cpu :
	$(CXX) functions.cpp $(CXXFLAGS) -o functions_cpu

functions_gpu :
	$(NVCC) functions.cu $(NVCCFLAGS) -o functions_gpu

functions_mic :
	$(CXX) functions.cpp $(CXXFLAGS) -mmic -o functions_mic
