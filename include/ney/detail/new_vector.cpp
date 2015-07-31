#include "../main.hpp"
#include "../main.hpp"
#include "../new_vector.hpp"

inline
new_vector::new_vector() : size_(10)
{
}

inline
new_vector::new_vector(unsigned int size) : size_(size)
{
}

inline new_vector&
new_vector::size(unsigned int size)
{
    size_ = size;

    return *this;
}
