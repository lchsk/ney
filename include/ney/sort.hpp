#ifndef NEY_SORT_HPP_
#define NEY_SORT_HPP_

#include "vector.hpp"

#if CC_CUDA
#include "cuda/sort.cuh"
#endif

NEY_NS_BEGIN

//! Merge sort

template <typename T>
class sort : public base_operation<T, sort>
{
    public:

        //! Constructor takes vector as argument

        sort(vector<T>& v);

        ~sort();

        //! Runs a function. It should be called from a status object

        void run() const;

    private:
        friend class status;
        vector<T>& a_;
        T* b_;

        void merge_sort(int low, int high) const;
        void merge(int, int, int) const;
};

#include "detail/sort.cpp"

NEY_NS_END

#endif
