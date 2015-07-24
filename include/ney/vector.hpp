#include "main.hpp"
#include "new_vector.hpp"

#ifndef NEY_VECTOR_HPP_
#define NEY_VECTOR_HPP_

NEY_NS_BEGIN

template <typename T>
class vector
{
    public:
        vector(const new_vector& config);
        ~vector();

        size_t size() const;

        void reset();

        vector& operator<<(T x);
        template <typename T>
        friend std::ostream& operator<<(std::ostream& s, const vector<T>& v);

        T& operator[] (unsigned index);
        T operator[] (unsigned index) const;

        vector& from (unsigned x);
        vector& to (unsigned x);
        vector& stride (unsigned x);
        vector& slice(unsigned from, unsigned to, unsigned stride = 1);

        // should be private!!!
        T* data_;



    private:
        const new_vector config_;

        // for << operator
        unsigned incr;

        unsigned from_;
        unsigned to_;
        unsigned stride_;


};

#include "detail/vector.inl"
NEY_NS_END

#endif
