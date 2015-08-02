#ifndef NEY_COUNT_HPP_
#define NEY_COUNT_HPP_

#include "vector.hpp"

NEY_NS_BEGIN

//! Counts how many given elements are there in a vector

template <typename T>
class count : public base_operation<T, count>
{
    public:

        //! Constructor takes value to be counted as an argument
        count(T value);

        ~count(){};

        //! Specifies vector used for search

        count& in(vector<T>& v);
        
        //! After finishing execution, the output will be saved in a variable specified by this function

        count& output(int& output);
        
        //! Runs a function. It should be called from a status object
        void run() const;

    private:
        friend class status;
        T value_;
        vector<T>* v_;
        mutable int* count_;
        

};

#include "detail/count.cpp"

NEY_NS_END

#endif
