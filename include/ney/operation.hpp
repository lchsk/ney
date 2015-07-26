#include "main.hpp"

#ifndef NEY_OPERATION_HPP_
#define NEY_OPERATION_HPP_

NEY_NS_BEGIN

class status;

template <class T, template <typename> class Derived_ >
class operation
{
    public:
        typedef Derived_<T> DerivedType;
        operation();
        virtual ~operation(){};

        virtual DerivedType& time();
        virtual void run() const = 0;
        std::string msg;
        // virtual operation& cast() = 0;

    private:
        friend class status;
        bool time_;

};

#include "detail/operation.inl"

NEY_NS_END

#endif
