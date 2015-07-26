#include "../operation.hpp"

template <class T, template <typename> class Derived>
inline
operation<T, Derived>::operation() : time_(false)
{}

template <class T, template <typename> class Derived>
inline Derived<T>& operation<T, Derived>::time()
{
    time_ = true;

    return static_cast<Derived<T> &>(*this);
}
