#include "../fill.hpp"
#include "../vector.hpp"
// #include <typeinfo>

template <typename T>
inline fill<T>::
// fill(const vector<T>& vec)
fill(vector<T>& v) : out(v)
{
    // for (int i = out.from(); i < out.to(); i += out.stride())
    // {
    //     out.data_[i] = value_;
    // }
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
        for (int i = out.from(); i < out.to(); i += out.stride())
        {
            out.data_[i] = value_;
        }

    }
    else if (ney::config.target == GPU)
    {

    }

    // return *this;
}
