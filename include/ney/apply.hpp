#ifndef NEY_APPLY_HPP_
#define NEY_APPLY_HPP_

#include "vector.hpp"

NEY_NS_BEGIN

/* 
    Use cases:

(1) apply(sin).vector1(vec1); -> output in vec1
(2) apply(add).vector1(vec1).vector2(vec2); -> output in vec1
(3) apply(add).vector1(vec1).vector2(vec2).value(scalar); -> output in vec1
(4) apply(add).vector1(vec1).value(scalar); -> output in vec1

Use output() function to redirect output to another vector.

*/

enum mode_t{
    FUN_VEC
};

template <typename T>
class apply : public base_operation<T, apply>
{
    public:
        // use cases 2, 3, 4
        apply(operation::operation_t op);

        // use case 1
        apply(function::function_t f);
        ~apply(){};

        apply& vector1(vector<T>& v);
        apply& vector2(vector<T>& v);
        apply& value(T value);
        apply& output(vector<T>& v);

        void run() const;

    private:
        friend class status;

        bool use_scalar_;
        T value_;

        vector<T>* v1_;
        vector<T>* v2_;
        mutable vector<T>* output_;
        operation::operation_t op_;
        function::function_t f_;

};

#include "detail/apply.cpp"

NEY_NS_END

#endif
