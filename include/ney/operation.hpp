#include "main.hpp"

#ifndef NEY_OPERATION_HPP_
#define NEY_OPERATION_HPP_

NEY_NS_BEGIN

class status;

template <class T, template <typename> class Derived>
class operation
{
    public:
        operation();
        virtual ~operation(){};

        virtual Derived<T>& time();
        virtual void run() const = 0;

    private:
        friend class status;
        bool time_;
};

#include "detail/operation.inl"

NEY_NS_END

#endif
