#include "../main.hpp"
#include "../compare.hpp"
#include "../vector.hpp"

template <typename T>
inline compare<T>::
compare() : v1_(NULL), v2_(NULL), output_(NULL)
{
    this->detect_data_type();
}

template <typename T>
inline
compare<T>& compare<T>::vector1(vector<T>& v)
{
    v1_ = &v;

    return *this;
}

template <typename T>
inline
compare<T>& compare<T>::vector2(vector<T>& v)
{
    v2_ = &v;

    return *this;
}

template <typename T>
inline
compare<T>& compare<T>::output(vector<bool>& v)
{
    output_ = &v;

    return *this;
}


template <typename T>
inline
void compare<T>::run() const
{
    if (ney::config.target == Intel)
    {   
        if (this->is_integer_)
        {
            for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
            {
                (*output_)[i] = ((*v1_)[i] == (*v2_)[i]) ? true : false;
            }
        }
        else
        {
            for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
            {
                (*output_)[i] = (fabs((*v1_)[i] - (*v2_)[i]) < this->precision_) ? true : false;
            }
        }
    }
    else if (ney::config.target == GPU)
    {

    }
}
