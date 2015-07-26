#include "../main.hpp"
#include "../new_vector.hpp"
#include <iostream>

inline
new_vector::new_vector() : size_(10)
{
}

inline new_vector&
new_vector::size(unsigned int size)
{
    size_ = size;

    return *this;
}
