#ifndef NEY_REPLACE_HPP_
#define NEY_REPLACE_HPP_

#include "vector.hpp"

#if CC_CUDA
#include "cuda/replace.cuh"
#endif

NEY_NS_BEGIN

//! Replace all specified elements in a vector with another value

template <typename T>
class replace : public base_operation<T, replace>
{
    public:

        //! Constructor takes value that needs to be replaced
        replace(T old_value);

        ~replace(){};

        //! Specify a new value
        replace& with(T new_value);

        //! Vector in which changes will be made

        replace& in(vector<T>& v);

        //! Runs a function, it should be called from a status object
        void run() const;

    private:
        friend class status;
        T old_;
        T new_;
        vector<T>* v_;
};

#include "detail/replace.cpp"

NEY_NS_END

#endif
