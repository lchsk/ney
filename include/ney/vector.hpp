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
        vector(const vector& that);

        
        vector& operator=(vector other);

        ~vector();

        size_t size() const;
        size_t length() const;

        vector& reset();

        vector& operator<<(T x);

        template <typename T2>
        friend std::ostream& operator<<(std::ostream& s, const vector<T2>& v);

        T& operator[] (unsigned index);
        T operator[] (unsigned index) const;

        vector& from (unsigned x);
        vector& to (unsigned x);
        vector& stride (unsigned x);
        vector& slice(unsigned from, unsigned to, unsigned stride = 1);

        unsigned from () const;
        unsigned to () const;
        unsigned stride () const;

        



    private:
        new_vector config_;

        template <typename T2>
        friend class fill;

        void swap(vector& second);

        // for << operator
        unsigned incr_;

        unsigned from_;
        unsigned to_;
        unsigned stride_;

        T* data_;

};

#include "detail/vector.cpp"
NEY_NS_END

#endif
