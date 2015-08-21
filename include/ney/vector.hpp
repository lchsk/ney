#include "main.hpp"
#include "new_vector.hpp"

#ifndef NEY_VECTOR_HPP_
#define NEY_VECTOR_HPP_

NEY_NS_BEGIN

//! A vector class
/*!
    Implementation of a vector class that can take a template argument. It also makes sure
    that stored data is properly aligned on Intel Xeon/Xeon Phi.
*/

template <typename T>
class vector
{
    template <typename T1>
    friend class open;
    template <typename T1>
    friend class compare;

    public:

        //! Default constructor. Vector can be specified as: ney::vector<T> v;

        vector();

        //! That's a constructor used for allocating memory and setting default parameters

        vector(const new_vector& config);

        //! A copy constructor. When used, data related to slicing is reset

        vector(const vector& that);

        //! Assignment operator. Copies data as well as slicing information

        vector& operator=(vector other);

        ~vector();

        //! Returns size of the data, ie., number of stored elements. Slicing does not change this value

        size_t size() const;

        //! Returns number of elements that will be affected by operations (eg., `reduce` or `random` function)

        size_t length() const;

        //! Resets slicing information (ie., values set by functions: `from()`, `to()`, `stride()`)

        vector& reset();

        //! A quick way to initialise a vector (perhaps for debugging) is to use << operator. For instance: `vector1 << 1 << 2 << 3 << 4;`. After that `vector1` will contain numbers 1, 2, 3 and 4

        vector& operator<<(T x);

        //! << operator can be used to print a vector, eg. `std::cout << vector1 << std::endl;`

        template <typename T2>
        friend std::ostream& operator<<(std::ostream& s, const vector<T2>& v);

        //! Changes a value of a vector by element such as this: `vector1[0] = 100;`

        T& operator[] (unsigned index);

        //! Reads a value stored in a vector such as this: `int value = vector1[0];`

        T operator[] (unsigned index) const;

        vector operator+(const vector& v) const;

        //! Sets a starting point for a slice

        vector& from (unsigned x);

        //! Sets an ending point for a slice (an element at an ending index is not included in a slice)

        vector& to (unsigned x);

        //! Sets a stride for a slice. If stride is equal to 2, then every second value will be selected by a slice

        vector& stride (unsigned x);

        //! Sets all `slice` values at once. `stride` can be omitted a by default is equal to 1

        vector& slice(unsigned from, unsigned to, unsigned stride = 1);

        //! Returns starting point of a slice

        unsigned from () const;

        //! Returns an ending point of a slice

        unsigned to () const;

        //! Returns stride value of a slice

        unsigned stride () const;

    private:

        //! Stores internal configuration data of a vector

        new_vector config_;

        //! Used in assignment operator implementation

        void swap(vector& second);

        //! Used for << implementation

        unsigned incr_;

        unsigned from_;
        unsigned to_;
        unsigned stride_;

        //! Vector data

        T* data_;
};

#include "detail/vector.cpp"
NEY_NS_END

#endif
