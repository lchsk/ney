#include "../main.hpp"
#include "../reduce.hpp"
#include "../vector.hpp"

template <typename T>
inline reduce<T>::
reduce(vector<T>& v) : v_(v), init_value_(0), output_(NULL), operation_(operation::none)
{
}

template <typename T>
inline
reduce<T>& reduce<T>::use(operation::operation_t t)
{
    operation_ = t;

    return *this;
}

template <typename T>
inline
reduce<T>& reduce<T>::output(T& output)
{
    output_ = &output;

    return *this;
}

template <typename T>
inline
reduce<T>& reduce<T>::init(T init_value)
{
    init_value_ = init_value;

    return *this;
}

template <typename T>
inline
void reduce<T>::run() const
{
    *output_ = init_value_;

    T r = *output_;

    if (ney::config.target == Intel)
    {
        if (operation_ == operation::add)
        {
            #pragma omp parallel for schedule(static) reduction(+:r)
            for (int i = v_.from(); i < v_.to(); i += v_.stride())
            {
                r += v_[i];
            }
        }
        else if (operation_ == operation::mul)
        {
            #pragma omp parallel for schedule(static) reduction(*:r)
            for (int i = v_.from(); i < v_.to(); i += v_.stride())
            {
                r *= v_[i];
            }
        }

        *output_ = r;
    }
    else if (ney::config.target == GPU)
    {

    }
}
