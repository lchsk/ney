#ifndef NEY_REPLACE_HPP_
#define NEY_REPLACE_HPP_

#include "vector.hpp"

NEY_NS_BEGIN

template <typename T>
class replace : public operation<T, replace>
{
    public:
        replace(T old_value);
        ~replace(){};

        replace& with(T new_value);
        replace& in(vector<T>& v);
        
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
