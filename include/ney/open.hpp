#include "vector.hpp"

#ifndef NEY_OPEN_HPP_
#define NEY_OPEN_HPP_

#include <cstdio>
// #include <iostream>
#include <iterator>
#include <istream>
#include <fstream>

NEY_NS_BEGIN

//! Opens a file

template <typename T>
class open : public base_operation<T, open>
{
    public:

        //! Constructor

        open(std::string path);

        //! Provide vector as an argument

        open& output(vector<T>& v);

        ~open(){};

        //! File will be treated as text

        open& as_text();

        //! Runs a function. Should be called by a status object. Alternatively, can be called openly if status object is not used

        void run() const;

    private:
        friend class status;
        vector<T>* v_;
        std::string path_;
        bool parallel_;
        bool as_text_;
};

#include "detail/open.cpp"

NEY_NS_END

#endif
