#ifndef NEY_CUDA_APPLY_HPP_
#define NEY_CUDA_APPLY_HPP_

#include "../ney.hpp"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/copy.h>
#include "strided_it.cuh"

NEY_NS_BEGIN
namespace gpu{

// template <typename T>
// __host__ __device__ T sine(T x)
// {
//     return sin(x);
// }


struct sine
{
    sine() {};

    template <typename T>
    __host__ __device__
    void operator()(T &y) const
    {
        y = sin(y);
    }
};

struct cosine
{
    cosine() {};

    template <typename T>
    __host__ __device__
    void operator()(T &y) const
    {
        y = cos(y);
    }
};

struct lower
{
    lower() {};

    template <typename T>
    __host__ __device__
    void operator()(T &y) const
    {
        if (y >= 'A' && y <= 'Z')
            y = y + 32;
    }
};

struct upper
{
    upper() {};

    template <typename T>
    __host__ __device__
    void operator()(T &y) const
    {
        if (y >= 'a' && y <= 'z')
            y = y - 32;
    }
};

template <typename T>
void apply(ney::vector<T>& output, ney::vector<T>& v1, ney::function::function_t t, bool v1_output_equal)
{
    if (v1.host_active())
        v1.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    if ( ! v1_output_equal)
    {
        if (output.host_active())
            output.copy_to_gpu();

        // have to copy v1 into output
        thrust::copy(v1.device().begin(), v1.device().end(),
                output.device().begin());
    }

    if (t != ney::function::none)
    {
        strided_range< Iterator > slice(output.device().begin() + output.from(), output.device().begin() + output.to(), output.stride());

        if (t == ney::function::sine)
            thrust::for_each(slice.begin(), slice.end(), sine());
        else if (t == ney::function::cosine)
            thrust::for_each(slice.begin(), slice.end(), cosine());
        else if (t == ney::function::lower)
            thrust::for_each(slice.begin(), slice.end(), lower());
        else if (t == ney::function::upper)
            thrust::for_each(slice.begin(), slice.end(), upper());
    }
}

// template <typename T>
// struct add2 : public thrust::binary_function<T, T, T>
// {
//     add2(){};
//
//     __host__ __device__
//     T operator()(const T& x, const T& y) const
//     {
//         return x + y;
//     }
// };

template <typename T>
void apply(ney::vector<T>& output, ney::vector<T>& v1, ney::vector<T>& v2, ney::operation::operation_t t, bool v1_output_equal)
{
    if (v1.host_active())
        v1.copy_to_gpu();

    if (v2.host_active())
        v2.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    if ( ! v1_output_equal)
    {
        if (output.host_active())
            output.copy_to_gpu();

        // have to copy v1 into output
        thrust::copy(v1.device().begin(), v1.device().end(),
                output.device().begin());
    }

    if (t != ney::operation::none)
    {
        strided_range< Iterator > s1(output.device().begin() + output.from(), output.device().begin() + output.to(), output.stride());
        strided_range< Iterator > s2(v2.device().begin() + v2.from(), v2.device().begin() + v2.to(), v2.stride());

        if (t == ney::operation::add)
            thrust::transform(s1.begin(), s1.end(), s2.begin(), s1.begin(), thrust::plus<T>());
        else if (t == ney::operation::mul)
            thrust::transform(s1.begin(), s1.end(), s2.begin(), s1.begin(), thrust::multiplies<T>());
    }
}



template <typename T>
void apply(ney::vector<T>& output, ney::vector<T>& v1, T value, ney::operation::operation_t t, bool v1_output_equal)
{
    if (v1.host_active())
        v1.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    if ( ! v1_output_equal)
    {
        if (output.host_active())
            output.copy_to_gpu();

        // have to copy v1 into output
        thrust::copy(v1.device().begin(), v1.device().end(),
                output.device().begin());
    }

    if (t != ney::operation::none)
    {
        strided_range< Iterator > s1(output.device().begin() + output.from(), output.device().begin() + output.to(), output.stride());

        if (t == ney::operation::add)
            thrust::for_each(s1.begin(), s1.end(), thrust::placeholders::_1 += value);
        else if (t == ney::operation::mul)
            thrust::for_each(s1.begin(), s1.end(), thrust::placeholders::_1 *= value);
    }
}

template <typename T>
void apply(ney::vector<T>& output, ney::vector<T>& v1, bool use_dvalue, double value, ney::operation::operation_t t, bool v1_output_equal)
{
    if (v1.host_active())
        v1.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    if ( ! v1_output_equal)
    {
        if (output.host_active())
            output.copy_to_gpu();

        // have to copy v1 into output
        thrust::copy(v1.device().begin(), v1.device().end(),
                output.device().begin());
    }

    if (t != ney::operation::none)
    {
        strided_range< Iterator > s1(output.device().begin() + output.from(), output.device().begin() + output.to(), output.stride());

        if (t == ney::operation::add)
            thrust::for_each(s1.begin(), s1.end(), thrust::placeholders::_1 += value);
        else if (t == ney::operation::mul)
            thrust::for_each(s1.begin(), s1.end(), thrust::placeholders::_1 *= value);
    }
}

template <typename T>
struct add2 : public thrust::binary_function<T, T, T>
{
    const T a;

    add2(T _a) : a(_a) {}

    __host__ __device__
        T operator()(const T& x, const T& y) const {
            return x + y + a;
        }
};

template <typename T>
struct mul2 : public thrust::binary_function<T, T, T>
{
    const T a;

    mul2(T _a) : a(_a) {}

    __host__ __device__
        T operator()(const T& x, const T& y) const {
            return x * y + a;
        }
};

template <typename T>
void apply(ney::vector<T>& output, ney::vector<T>& v1, ney::vector<T>& v2, T value, ney::operation::operation_t t, bool v1_output_equal)
{
    if (v1.host_active())
        v1.copy_to_gpu();

    if (v2.host_active())
        v2.copy_to_gpu();

    typedef typename thrust::device_vector<T>::iterator Iterator;

    if ( ! v1_output_equal)
    {
        if (output.host_active())
            output.copy_to_gpu();

        // have to copy v1 into output
        thrust::copy(v1.device().begin(), v1.device().end(),
                output.device().begin());
    }

    if (t != ney::operation::none)
    {
        strided_range< Iterator > s1(output.device().begin() + output.from(), output.device().begin() + output.to(), output.stride());
        strided_range< Iterator > s2(v2.device().begin() + v2.from(), v2.device().begin() + v2.to(), v2.stride());

        if (t == ney::operation::add)
            thrust::transform(s1.begin(), s1.end(), s2.begin(), s1.begin(), add2<T>(value));
        else if (t == ney::operation::mul)
            thrust::transform(s1.begin(), s1.end(), s2.begin(), s1.begin(), mul2<T>(value));
    }
}

}
NEY_NS_END

#endif
