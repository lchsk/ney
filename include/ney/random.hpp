#include "vector.hpp"

#ifndef NEY_RANDOM_HPP_
#define NEY_RANDOM_HPP_

NEY_NS_BEGIN

template <typename T>
class random : public operation<T, random>
{
    public:
        random(vector<T>& a);
        ~random(){};

        void run() const;
        random& min(T min);
        random& max(T max);

    private:
        friend class status;

        T min_;
        T max_;

        vector<T>& out;
};

#include "detail/random.inl"

NEY_NS_END

#endif
