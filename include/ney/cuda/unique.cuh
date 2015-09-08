#ifndef NEY_CUDA_UNIQUE_HPP_
#define NEY_CUDA_UNIQUE_HPP_

#include "../ney.hpp"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/unique.h>
#include <thrust/functional.h>

#include "strided_it.cuh"

NEY_NS_BEGIN
namespace gpu{

template <typename T>
int unique(ney::vector<T>& v)
{
    if (v.host_active())
        v.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    strided_range< Iterator > slice(v.device().begin() + v.from(), v.device().begin() + v.to(), v.stride());

    thrust::sort(v.device().begin(), v.device().end());

    v.device().erase(thrust::unique(v.device().begin(), v.device().end()), v.device().end());

    v.device().shrink_to_fit();

    // for (int i = 0; i < v.device().size(); i++)
    // {
    //     std::cout << v.device()[i] << "\n";
    // }

    // thrust::device_vector<T>::iterator new_end = thrust::unique(v.device().begin(), v.device().end());

    // for (int i = 0; i < 5; i++)
    // {
    //     std::cout << slice[i] << "\n";
    // }

    return v.device().size();
}

}
NEY_NS_END

#endif
