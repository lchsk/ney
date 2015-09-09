#include "../main.hpp"
#include "../random.hpp"
#include "../vector.hpp"
#include <iostream>

template <typename T>
inline random<T>::
random(vector<T>& v) : out(v), min_(0), max_(RAND_MAX)
{
}

template <typename T>
inline random<T>& random<T>::min(T min)
{
    min_ = min;

    return *this;
}

template <typename T>
inline random<T>& random<T>::max(T max)
{
    max_ = max;

    return *this;
}

template <typename T>
inline
void random<T>::run() const
{
    if (ney::config.target == Intel)
    {
        #pragma omp parallel for schedule(static)
        #pragma simd
        #pragma vector aligned
        for (int i = out.from(); i < out.to(); i += out.stride())
            out.set(i, min_ + static_cast <T> (rand()) / (static_cast<T> (RAND_MAX / (max_ - min_))));
    }
    #if CC_CUDA
    else if (ney::config.target == GPU)
    {
        ney::gpu::random<T>(out, min_, max_);
    }
    #endif
}
