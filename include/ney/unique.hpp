#include "vector.hpp"

#ifndef NEY_UNIQUE_HPP_
#define NEY_UNIQUE_HPP_

NEY_NS_BEGIN

//! Takes a vector as an argument and creates a set (vector with unique elemenets)

template <typename T>
class unique : public base_operation<T, unique>
{
    public:

        //! Constructor takes vector as an argument

        unique(vector<T>& v);

        ~unique(){};

        //! Output vector

        unique& output(vector<T>& v);

        //! Runs a function. Should be called by a status object. Alternatively, can be called openly if status object is not used

        void run() const;

    private:
        friend class status;
        vector<T>* out_;
        vector<T>& v_;
};

#include "detail/unique.cpp"

NEY_NS_END

#endif
