#ifndef NEY_COUNT_HPP_
#define NEY_COUNT_HPP_

#include "vector.hpp"

NEY_NS_BEGIN

template <typename T>
class count : public base_operation<T, count>
{
    public:
        count(T value);
        ~count(){};

        count& in(vector<T>& v);
        count& output(T& output);
        void run() const;

    private:
        friend class status;
        T value_;
        vector<T>* v_;
        mutable T* count_;
        

};

#include "detail/count.cpp"

NEY_NS_END

#endif
