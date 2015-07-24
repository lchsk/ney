

#ifndef NEY_OPERATION_HPP_
#define NEY_OPERATION_HPP_

class status;

class operation
{
    public:
        operation();

    private:
        friend class status;
};

#include "detail/operation.inl"

#endif
