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
        #pragma omp parallel for schedule(static)
        #pragma simd
        for (int i = out.from(); i < out.to(); i += out.stride())
            out[i] = value_;
    }
    else if (ney::config.target == GPU)
    {

    }
}
