#ifndef NEY_COMPARE_HPP_
#define NEY_COMPARE_HPP_

#include "vector.hpp"

NEY_NS_BEGIN

template <typename T>
class compare : public operation<T, compare>
{
    public:
        compare();
        ~compare(){};

        compare& vector1(vector<T>& v);
        compare& vector2(vector<T>& v);
        compare& output(vector<bool>& output);
        void run() const;

    private:
        friend class status;
        vector<T>* v1_;
        vector<T>* v2_;
        vector<bool>* output_;

};

#include "detail/compare.cpp"

NEY_NS_END

#endif
