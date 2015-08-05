#include "vector.hpp"

#ifndef NEY_SWAP_HPP_
#define NEY_SWAP_HPP_

NEY_NS_BEGIN

//! Swaps elements in two vectors or swaps elements in one vector separated by some distance

template <typename T>
class swap : public base_operation<T, swap>
{
    public:

        //! Constructor takes no arguments

        swap();

        ~swap(){};

        //! First input vector

        swap& vector1(vector<T>& v);

        //! Second input vector
        
        swap& vector2(vector<T>& v);

        //! Runs a function. Should be called by a status object. Alternatively, can be called openly if status object is not used

        void run() const;

    private:
        friend class status;
        vector<T>* v1_;
        vector<T>* v2_;
};

#include "detail/swap.cpp"

NEY_NS_END

#endif
