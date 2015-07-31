#include "../main.hpp"
#include "../vector.hpp"

template <typename T>
inline vector<T>::
vector(const new_vector& config)
    : config_(config)
    , incr_(0)
    , from_(0)
    , to_(config.size_)
    , stride_(1)
{
    #if ALIGNMENT_OK
        data_ = (T*) MALLOC (sizeof (T*) * config.size_, ALIGN);
    #else
        data_ = (T*) MALLOC (sizeof (T*) * config.size_);
    #endif

}

template <typename T>
inline vector<T>::
vector(const vector<T>& that)
{
    std::cout << "copy constructor\n";

    config_ = that.config_;

    #if ALIGNMENT_OK
        data_ = (T*) MALLOC (sizeof (T*) * config_.size_, ALIGN);
    #else
        data_ = (T*) MALLOC (sizeof (T*) * config_.size_);
    #endif

    for (int i = 0; i < config_.size_; i++)
    {
        data_[i] = that[i];
    }

    this->reset();

}

template <typename T>
inline
void vector<T>::swap(vector<T>& second)
{
    using std::swap;

    swap(this->data_, second.data_); 
    swap(this->config_, second.config_);

    swap(this->incr_, second.incr_);
    swap(this->to_, second.to_);
    swap(this->from_, second.from_);
    swap(this->stride_, second.stride_);
}

template <typename T>
inline
vector<T>& vector<T>::operator=(vector<T> other) // (1)
{
    swap(other); // (2)

    std::cout << "swapped\n";

    return *this;
}

template <typename T>
inline vector<T>::
~vector()
{
    if (data_ != NULL)
    {
        FREE (data_);
        data_ = NULL;
        std::cout << "\tDestructor" << std::endl;
    }
}

/**
    Size blablabal
*/
template <typename T>
inline size_t vector<T>::size() const
{
    return config_.size_;
}

template <typename T>
inline vector<T>& vector<T>::reset()
{
    incr_ = 0;
    from_ = 0;
    to_ = config_.size_;
    stride_ = 1;

    return *this;
}

template <typename T>
vector<T>& vector<T>::operator<<(T x)
{
    data_[incr_++] = x;
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const vector<T>& v)
{
    // print a vector
    #include <iostream>
    // #include <iomanip>

    std::cout << "vector(";

    // for (int i = 0; i < v.size(); i++)
    for (int i = v.from(); i < v.to(); i += v.stride())
    {
        std::cout << v[i];

        if (i < v.to() - v.stride())
                std::cout << ", ";
    }

    std::cout << ")" << std::endl;

    return s;
}

template <typename T>
inline T& vector<T>::operator[] (unsigned index)
{
    return data_[index];
}

template <typename T>
inline T vector<T>::operator[] (unsigned index) const
{
    return data_[index];
}

template <typename T>
inline vector<T>& vector<T>::from (unsigned x)
{
    from_ = x;
    return *this;
}

template <typename T>
inline vector<T>& vector<T>::to (unsigned x)
{
    to_ = x;
    return *this;
}

template <typename T>
inline vector<T>& vector<T>::stride (unsigned x)
{
    stride_ = x;
    return *this;
}

template <typename T>
inline unsigned vector<T>::from () const
{
    return from_;
}

template <typename T>
inline unsigned vector<T>::to () const
{
    return to_;
}

template <typename T>
inline unsigned vector<T>::stride () const
{
    return stride_;
}

template <typename T>
vector<T>& vector<T>::slice (unsigned from, unsigned to, unsigned stride)
{
    from_ = from;
    to_ = to;
    stride_ = stride;
    return *this;
}
