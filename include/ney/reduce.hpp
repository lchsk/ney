#ifndef NEY_REDUCE_HPP_
#define NEY_REDUCE_HPP_

#include "vector.hpp"
#include "cuda/reduce.cuh"

NEY_NS_BEGIN

//! Reduce a vector to the single value (eg., using addition, multiplication)

template <typename T>
class reduce : public base_operation<T, reduce>
{
    public:

        //! Constructor takes vector as an argument

        reduce(vector<T>& v);

        ~reduce(){};

        //! Specify operation that should be used (addition, multiplication)

        reduce& use(operation::operation_t t);

        //! Initalise output value, by default it takes 0

        reduce& init(T init_value);

        //! Output variable

        reduce& output(T& output);

        //! Runs the function. It should be called from the status object

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
