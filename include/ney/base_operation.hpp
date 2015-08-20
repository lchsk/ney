#include "main.hpp"

#ifndef NEY_BASE_OPERATION_HPP_
#define NEY_BASE_OPERATION_HPP_

NEY_NS_BEGIN

class status;

template <class T, template <typename> class Derived>
class base_operation
{
    public:
        base_operation();
        virtual ~base_operation(){};

        virtual Derived<T>& time();
        virtual Derived<T>& precision(T precision);
        virtual Derived<T>& condition(bool (*cond)(const T*, const T*));

        void detect_data_type();

        virtual void run() const = 0;

    protected:
        bool is_integer_;
        T precision_;
        bool (*cond_)(const T*, const T*);

    private:
        friend class status;
        bool time_;
};

#include "detail/base_operation.cpp"

NEY_NS_END

#endif
