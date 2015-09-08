#ifndef NEY_CUDA_SORT_HPP_
#define NEY_CUDA_SORT_HPP_

#include "../ney.hpp"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/functional.h>

#include "strided_it.cuh"

NEY_NS_BEGIN
namespace gpu{

template <typename T>
void sort(ney::vector<T>& v)
{
    if (v.host_active())
        v.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    strided_range< Iterator > slice(v.device().begin() + v.from(), v.device().begin() + v.to(), v.stride());
    thrust::sort(slice.begin(), slice.end());
}

}
NEY_NS_END

#endif
