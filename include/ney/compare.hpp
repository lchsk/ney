#ifndef NEY_COMPARE_HPP_
#define NEY_COMPARE_HPP_

#include "vector.hpp"

NEY_NS_BEGIN

//! Compares two vectors and returns a vector of boolean values, where `true` at each position means that elements in two input vectors are the same.

template <typename T>
class compare : public base_operation<T, compare>
{
    public:

        //! Constructor takes no arguments

        compare();

        ~compare(){};

        //! First input vector

        compare& vector1(vector<T>& v);

        //! Second input vector

        compare& vector2(vector<T>& v);

        //! Output vector of boolean values

        compare& output(vector<bool>& output);

        //! Runs a function. It should be called from a status object
        void run() const;

    private:
        friend class status;
        vector<T>* v1_;
        mutable vector<T>* v2_;
        vector<bool>* output_;
};

#include "detail/compare.cpp"

NEY_NS_END

#endif
