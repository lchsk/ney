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
        replace& precision(T precision);
        void run() const;

    private:
        friend class status;
        T old_;
        T new_;
        // vector<T>& v_;
        vector<T>* v_;
        bool is_integer_;
        T precision_;

};

#include "detail/replace.inl"

NEY_NS_END

#endif
