#include "../main.hpp"
#include "../fill.hpp"
#include "../vector.hpp"

template <typename T>
inline fill<T>::
fill(vector<T>& v) : out(v)
{
}

template <typename T>
inline
fill<T>& fill<T>::value(T value)
{
    value_ = value;

    return *this;
}

template <typename T>
inline
void fill<T>::run() const
{
    if (ney::config.target == Intel)
    {
        if (out.stride() == 1)
        {
            #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
            #pragma simd
            #pragma vector aligned
            for (int i = out.from(); i < out.to(); i++)
                out.set(i, value_);
        }
        else
        {
            #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
            #pragma simd
            #pragma vector aligned
            for (int i = out.from(); i < out.to(); i += out.stride())
                out.set(i, value_);
        }

    }
    #if CC_CUDA
    else if (ney::config.target == GPU)
    {
        ney::gpu::fill<T>(out, value_);
    }
    #endif
}
