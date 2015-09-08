#ifndef NEY_CUDA_REDUCE_HPP_
#define NEY_CUDA_REDUCE_HPP_

#include "../ney.hpp"

// namespace {

// // void reduce(T* data, int from, int to, int stride, int length, int init, int operation);
// extern void reduce(T* data);

// extern "C"{

// namespace gpu{

// template <typename T>
// void creduce(int a);

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
// #include <thrust/generate.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/inner_product.h>

NEY_NS_BEGIN
namespace gpu{

    // template <typename T>
    // __global__ void add(T* d)
    // {
    //      int tid = blockIdx.x; // handle the data at this index
    //      if (tid < N)
    //      c[tid] = a[tid] + b[tid];
    //  }

    // struct saxpy_functor
    // {
    //     const float a;
    //     saxpy_functor ( float _a) : a(_a) {}
    //     __host__ __device__ float operator() (const float & x, const float &y) const
    //     {
    //         return a * x + y;
    //     }
    // };

template <typename T>
// void reduce(T* data, int from, int to, int stride, int length, int init, int operation)

T reduce(ney::vector<T>& v, T init, ney::operation::operation_t t)
{
    T result;
    // thrust::device_vector<T> vec(v.length());

    // for (int i = v.from(); i < v.to(); i += v.stride())
    {
        // vec.push_back(v[i]);
    }

    if (t == ney::operation::add)
    {
        result = thrust::reduce(v.device().begin(), v.device().end(), init, thrust::plus<T>());
    }
    else if (t == ney::operation::mul)
    {
        // thrust::transform (X.begin(), X.end(), Y.begin(), Y.begin(), saxpy_functor(A));

        // T* dev;
        // cudaMalloc((void**) &dev, v.length() * sizeof(T));
        //
        // cudaMemcpy(dev, v.raw(), v.length() * sizeof(T), cudaMemcpyHostToDevice);

        // std::cout << "mul\n";
        // std::cout << init << "\n";
        // result = thrust::inner_product(vec.begin(), vec.end(), vec.begin(), 1   );
        result = thrust::reduce(v.device().begin(), v.device().end(), init, thrust::multiplies<int>());
    }

    return result;
}

}
NEY_NS_END

#endif
