#include "../main.hpp"
#include "../base_operation.hpp"

template <class T, template <typename> class Derived>
inline
base_operation<T, Derived>::base_operation() : time_(false), is_integer_(true)
{}

template <class T, template <typename> class Derived>
inline Derived<T>& base_operation<T, Derived>::time()
{
    time_ = true;

    return static_cast<Derived<T> &>(*this);
}

template <class T, template <typename> class Derived>
inline Derived<T>& base_operation<T, Derived>::precision(T precision)
{
    precision_ = precision;

    return static_cast<Derived<T> &>(*this);
}

template <class T, template <typename> class Derived>
inline void base_operation<T, Derived>::detect_data_type()
{
    if (2 == (T) 2.5)
        is_integer_ = true;
    else
    {
        is_integer_ = false;
        precision_ = 0.00001;
    }
}
