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
    config_ = that.config_;
    config_.size_ = that.length();

    #if ALIGNMENT_OK
        data_ = (T*) MALLOC (sizeof (T*) * that.length(), ALIGN);
    #else
        data_ = (T*) MALLOC (sizeof (T*) * that.length());
    #endif

    int j = 0;

    for (int i = that.from(); i < that.to(); i += that.stride())
    {
        data_[j++] = that[i];
    }

    this->reset();
}

template <typename T>
inline vector<T>::
vector()
    :
    // config_(NULL)
    // ,
    incr_(0)
    , from_(0)
    , to_(0)
    , stride_(1)
{
    data_ = NULL;
}

template <typename T>
inline
void vector<T>::swap_(vector<T>& second)
{
    // using std::swap;

    std::swap(this->data_, second.data_);
    std::swap(this->config_, second.config_);

    std::swap(this->incr_, second.incr_);
    std::swap(this->to_, second.to_);
    std::swap(this->from_, second.from_);
    std::swap(this->stride_, second.stride_);
}

template <typename T>
inline
vector<T>& vector<T>::operator=(vector<T> other)
{
    swap_(other);

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
    }
}

template <typename T>
inline size_t vector<T>::size() const
{
    return config_.size_;
}

template <typename T>
inline size_t vector<T>::length() const
{
    return ceil((to_ - from_) / (float)stride_);
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
    std::cout << "vector(";

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
inline T* vector<T>::raw() const
{
    return data_;
}

template <typename T>
inline vector<T> vector<T>::operator+(const vector<T>& v) const
{
    vector<T> out_ = new_vector().size(this->length() + v.length());
    int j = 0;

    for (int i = from_; i < to_; i += stride_)
    {
        out_[j++] = data_[i];
    }

    for (int i = v.from(); i < v.to(); i += v.stride())
    {
        out_[j++] = v.data_[i];
    }

    return out_;
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
