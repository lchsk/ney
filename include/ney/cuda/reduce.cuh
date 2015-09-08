#ifndef NEY_CUDA_REDUCE_HPP_
#define NEY_CUDA_REDUCE_HPP_

#include "../ney.hpp"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>

#include "strided_it.cuh"

NEY_NS_BEGIN
namespace gpu{

template <typename T>
T reduce(ney::vector<T>& v, T init, ney::operation::operation_t t)
{
    T result;

    if (v.host_active())
        v.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    strided_range< Iterator > slice(v.device().begin() + v.from(), v.device().begin() + v.to(), v.stride());

    if (t == ney::operation::add)
    {
        result = thrust::reduce(slice.begin(), slice.end(), init, thrust::plus<T>());
    }
    else if (t == ney::operation::mul)
    {
        // T* dev;
        // cudaMalloc((void**) &dev, v.length() * sizeof(T));
        //
        // cudaMemcpy(dev, v.raw(), v.length() * sizeof(T), cudaMemcpyHostToDevice);

        result = thrust::reduce(slice.begin(), slice.end(), init, thrust::multiplies<T>());
    }

    return result;
}

}
NEY_NS_END

#endif
