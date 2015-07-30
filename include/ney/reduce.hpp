#ifndef NEY_REDUCE_HPP_
#define NEY_REDUCE_HPP_

#include "vector.hpp"

NEY_NS_BEGIN

template <typename T>
class reduce : public base_operation<T, reduce>
{
    public:
        reduce(vector<T>& v);
        ~reduce(){};

        reduce& use(operation::operation_t t);
        reduce& init(T init_value);
        reduce& output(T& output);

        void run() const;

    private:
        friend class status;

        operation::operation_t operation_;
        T* output_;
        T init_value_;
        vector<T>& v_;

};

#include "detail/reduce.cpp"

NEY_NS_END

#endif
