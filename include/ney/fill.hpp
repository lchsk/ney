#include "vector.hpp"

#ifndef NEY_FILL_HPP_
#define NEY_FILL_HPP_

NEY_NS_BEGIN

template <typename T>
class fill : public operation
{
    public:
        fill(vector<T>& a);

    private:
        friend class status;

        fill& run() const;

        vector<T>& out;
};

#include "detail/fill.inl"

NEY_NS_END

#endif
