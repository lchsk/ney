#ifndef NEY_CUDA_RANDOM_HPP_
#define NEY_CUDA_RANDOM_HPP_

#include "../ney.hpp"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/random.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>

#include "strided_it.cuh"

NEY_NS_BEGIN
namespace gpu{

template <typename T>
struct prg_int
{
    T a, b;
    int seed;

    __host__ __device__
    prg_int(T _a, T _b, unsigned int _seed) : a(_a), b(_b), seed(_seed) {};

    __host__ __device__
    T operator()(const unsigned int n) const
    {
        thrust::default_random_engine rng(seed);
        thrust::uniform_int_distribution<T> dist(a, b);
        rng.discard(n);

        return dist(rng);
    }
};

template <typename T>
struct prg_real
{
    T a, b;
    int seed;

    __host__ __device__
    prg_real(T _a, T _b, unsigned int _seed) : a(_a), b(_b), seed(_seed) {};

    __host__ __device__
    T operator()(const unsigned int n) const
    {
        thrust::default_random_engine rng(seed);
        thrust::uniform_real_distribution<T> dist(a, b);
        rng.discard(n);

        return dist(rng);
    }
};

template <typename T>
void random(ney::vector<T>& v, T min, T max)
{
    if (v.host_active())
        v.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;
    // thrust::counting_iterator<unsigned int> index_sequence_begin(0);

    strided_range< Iterator > slice(v.device().begin() + v.from(), v.device().begin() + v.to(), v.stride());

    if (v.is_int())
    {
        thrust::transform(thrust::make_counting_iterator(1),
            thrust::make_counting_iterator((int) v.size() + 1),
            slice.begin(),
            prg_int<T>(min, max, time(NULL)));
    }
    else
    {
        thrust::transform(thrust::make_counting_iterator(1),
            thrust::make_counting_iterator((int) v.size() + 1),
            slice.begin(),
            prg_real<T>(min, max, time(NULL)));
    }
}

}
NEY_NS_END

#endif
