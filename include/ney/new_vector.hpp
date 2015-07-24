#include "main.hpp"

#ifndef NEY_NEW_VECTOR_HPP_
#define NEY_NEW_VECTOR_HPP_

NEY_NS_BEGIN

template <typename T>
class vector;

class new_vector
{
    public:
        new_vector();
        new_vector& size(unsigned int size);

    private:
        template <typename T> friend class vector;
        size_t size_;
};

#include "detail/new_vector.inl"
NEY_NS_END

#endif
