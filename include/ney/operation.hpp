#include "main.hpp"

#ifndef NEY_OPERATION_HPP_
#define NEY_OPERATION_HPP_

NEY_NS_BEGIN

class status;

template <typename T>
class operation
{
    public:
        operation();
        virtual ~operation(){};

        virtual operation& time();
        virtual void run() const = 0;

    private:
        friend class status;
        bool time_;

};

#include "detail/operation.inl"

NEY_NS_END

#endif
