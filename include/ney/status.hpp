#ifndef NEY_STATUS_HPP_
#define NEY_STATUS_HPP_

NEY_NS_BEGIN

class status
{
    public:
        template <typename T> status(const fill<T>& obj);

};

#include "detail/status.inl"

NEY_NS_END

#endif
