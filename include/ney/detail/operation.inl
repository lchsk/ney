#include "../operation.hpp"

template <typename T>
inline
operation<T>::operation() : time_(false)
{}

template <typename T>
inline operation<T>& operation<T>::time()
{
    time_ = true;

    return *this;
}
