#include "../operation.hpp"

template <class T, template <typename> class Derived_ >
inline
operation<T, Derived_>::operation() : time_(false), msg("operation")
{}

template <class T, template <typename> class Derived_ >
inline Derived_<T>& operation<T, Derived_>::time()
{
    time_ = true;

    std::cout << "where: " << this->msg << std::endl;

    return static_cast<Derived_<T> &>(*this);

    // operation<T>& tmp = cast();
    // std::cout << "where: " << tmp.msg << std::endl;

    // this->cast();

    // return this->cast();
    // return this->cast(this);
    // return *this;
}
