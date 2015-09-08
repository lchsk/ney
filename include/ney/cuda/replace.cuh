#ifndef NEY_CUDA_REPLACE_HPP_
#define NEY_CUDA_REPLACE_HPP_

#include "../ney.hpp"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/replace.h>
#include <thrust/functional.h>

#include "strided_it.cuh"

NEY_NS_BEGIN
namespace gpu{

template <typename T>
void replace(ney::vector<T>& v, T o, T n)
{
    if (v.host_active())
        v.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    strided_range< Iterator > slice(v.device().begin() + v.from(), v.device().begin() + v.to(), v.stride());
    thrust::replace(slice.begin(), slice.end(), o, n);
}

}
NEY_NS_END

#endif
