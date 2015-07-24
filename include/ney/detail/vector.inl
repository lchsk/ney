#include "../main.hpp"
#include "../vector.hpp"
#include <iostream>

template <typename T>
inline vector<T>::
vector(const new_vector& config)
    : config_(config)
    , incr(0)
    , from_(0)
    , to_(config.size_)
    , stride_(1)
{
    std::cout << config.size_ << std::endl;

    #if USE_ALIGNMENT
        data_ = (T*) MALLOC (sizeof (T*) * config.size_, ALIGN);
    #else
        data_ = (T*) MALLOC (sizeof (T*) * config.size_);
    #endif

}

template <typename T>
inline vector<T>::
~vector()
{
    std::cout << "Bye" << std::endl;

    if (data_ != NULL)
        FREE (data_);
}

template <typename T>
inline size_t vector<T>::size() const
{
    return config_.size_;
}

template <typename T>
inline void vector<T>::reset()
{
    incr = 0;
}

template <typename T>
vector<T>& vector<T>::operator<<(T x)
{
    data_[incr++] = x;
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const vector<T>& v)
{
    // print a vector
    #include <iostream>
    // #include <iomanip>

    std::cout << "vector(";

    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i];

        if (i < v.size() - 1)
                std::cout << ", ";
    }

    std::cout << ")" << std::endl;


    //
    // for (int i = 0; i < v.size(); i++)
    // {
    //     std::cout << std::setw(10) << v[i];
    //
    //     if (i < v.size() - 1)
    //         std::cout << ", ";
    //
    //     if ((i + 1) % 5 == 0)
    //         std::cout << std::endl << " ";
    // }
    //
    // std::cout << ")" << std::endl;

    return s;
}

template <typename T>
T& vector<T>::operator[] (unsigned index)
{
    return data_[index];
}

template <typename T>
T vector<T>::operator[] (unsigned index) const
{
    return data_[index];
}

template <typename T>
vector<T>& vector<T>::from (unsigned x)
{
    from_ = x;
    return *this;
}

template <typename T>
vector<T>& vector<T>::to (unsigned x)
{
    to_ = x;
    return *this;
}

template <typename T>
vector<T>& vector<T>::stride (unsigned x)
{
    stride_ = x;
    return *this;
}

template <typename T>
vector<T>& vector<T>::slice (unsigned from, unsigned to, unsigned stride)
{
    from_ = from;
    to_ = to;
    stride_ = stride;
    return *this;
}
