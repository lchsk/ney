#ifndef NEY_CUDA_REDUCE_HPP_
#define NEY_CUDA_REDUCE_HPP_

// #include "../ney.hpp"

// namespace {

// // void reduce(T* data, int from, int to, int stride, int length, int init, int operation);
// extern void reduce(T* data);

// extern "C"{

// namespace gpu{

// template <typename T>
// void creduce(int a);

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/random.h>

template <typename T>
void creduce(T* data, int from, int to, int stride, int length, int init, int operation)
{
    // std::cout << a << "\n";
    // std::cout << sizeof(a) << "\n";

    thrust::device_vector<T> vec(length);
    //
    int j = 0;
    for (int i = from; i < to; i += stride)
    {
        vec[j++] = data[i];
    }

    thrust::plus<int> binary_op;

    int sum = thrust::reduce(vec.begin(), vec.end(), init, binary_op);

    std::cout << "sum is " << sum << std::endl;
}

// }
// }
// };

#endif
