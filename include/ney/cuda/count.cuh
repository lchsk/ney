#ifndef NEY_CUDA_COUNT_HPP_
#define NEY_CUDA_COUNT_HPP_

#include "../ney.hpp"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/count.h>
#include <thrust/functional.h>

#include "strided_it.cuh"

NEY_NS_BEGIN
namespace gpu{

template <typename T>
int count(ney::vector<T>& v, T value)
{
    int result;

    if (v.host_active())
        v.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    strided_range< Iterator > slice(v.device().begin() + v.from(), v.device().begin() + v.to(), v.stride());

    result = thrust::count(slice.begin(), slice.end(), value);

    return result;
}

}
NEY_NS_END

#endif
