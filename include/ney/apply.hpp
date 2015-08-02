#ifndef NEY_APPLY_HPP_
#define NEY_APPLY_HPP_

#include "vector.hpp"

NEY_NS_BEGIN




// enum mode_t{
//     FUN_VEC
// };

//! `apply` function can be used in several modes. Can apply a function to the whole vector or apply an operation on two vectors and/or scalar
/** 
    Use cases:

(1) apply(sin).vector1(vec1); -> output in vec1
(2) apply(add).vector1(vec1).vector2(vec2); -> output in vec1
(3) apply(add).vector1(vec1).vector2(vec2).value(scalar); -> output in vec1
(4) apply(add).vector1(vec1).value(scalar); -> output in vec1

Use output() function to redirect output to another vector.

*/

template <typename T>
class apply : public base_operation<T, apply>
{
    public:
        //! Constructor for use cases 2, 3, 4 (takes an operation constant as an argument)
        
        apply(operation::operation_t op);

        //! Constructor fror use case 1 (takes a function constant as an argument)
        
        apply(function::function_t f);

        ~apply(){};

        //! First input vector

        apply& vector1(vector<T>& v);
        
        //! Second input vector

        apply& vector2(vector<T>& v);
        
        //! Scalar value that can be used in use cases 3 and 4

        apply& value(T value);
        
        //! Redirect output to another vector
        apply& output(vector<T>& v);

        //! Runs the function. It should be called from a status object
        
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
