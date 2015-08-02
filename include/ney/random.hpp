#include "vector.hpp"

#ifndef NEY_RANDOM_HPP_
#define NEY_RANDOM_HPP_

NEY_NS_BEGIN

//! Fill a vector with random numbers

template <typename T>
class random : public base_operation<T, random>
{
    public:

        //! Constructor takes a vector as an argument

        random(vector<T>& a);

        ~random(){};

        //! Runs a function. It should be called from a status object

        void run() const;

        //! Minimum value in a range of generated numbers (inclusive)

        random& min(T min);

        //! Maximum value in a range of generated numbers (exclusive)
        
        random& max(T max);

    private:
        friend class status;

        T min_;
        T max_;

        vector<T>& out;
};

#include "detail/random.cpp"

NEY_NS_END

#endif
