#include "vector.hpp"

#ifndef NEY_FILL_HPP_
#define NEY_FILL_HPP_

NEY_NS_BEGIN

//! Fills a vector with a specified value. Can fill a part of a vector and/or use a stride.

template <typename T>
class fill : public base_operation<T, fill>
{
    public:

        //! Constructor takes a vector as an argument
        
        fill(vector<T>& a);

        ~fill(){};

        //! Specifies with what value a vector should be filled with

        fill& value(T value);

        //! Runs a function. Should be called by a status object. Alternatively, can be called openly if status object is not used

        void run() const;

    private:
        friend class status;
        unsigned int value_;
        vector<T>& out;
};

#include "detail/fill.cpp"

NEY_NS_END

#endif
