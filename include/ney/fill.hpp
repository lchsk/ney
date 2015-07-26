#include "vector.hpp"

#ifndef NEY_FILL_HPP_
#define NEY_FILL_HPP_

NEY_NS_BEGIN

template <typename T>
class fill : public operation<T, fill>
{
    public:
        fill(vector<T>& a);
        ~fill(){};

        fill& value(T value);
        void run() const;

    private:
        friend class status;
        T value_;
        vector<T>& out;
};

#include "detail/fill.inl"

NEY_NS_END

#endif
