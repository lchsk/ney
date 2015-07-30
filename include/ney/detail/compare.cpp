#include "../main.hpp"
#include "../compare.hpp"
#include "../vector.hpp"

template <typename T>
inline compare<T>::
compare()
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
                if ((*v1_)[i] == (*v2_)[i])
                    (*output_)[i] = true;
            }
        }
        else
        {
            for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
            {
                if ((*v1_)[i] > ((*v2_)[i] - this->precision_) && (*v1_)[i] < ((*v2_)[i] + this->precision_))
                    (*output_)[i] = true;
            }
        }
    }
    else if (ney::config.target == GPU)
    {

    }
}
