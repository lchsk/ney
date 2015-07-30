#include "../main.hpp"
#include "../replace.hpp"
#include "../vector.hpp"

template <typename T>
inline replace<T>::
replace(T old_value) : old_(old_value)
{
    if (2 == (T) 2.5)
        is_integer_ = true;
    else
    {
        is_integer_ = false;
        precision_ = 0.00001;
    }
}

template <typename T>
inline
replace<T>& replace<T>::with(T new_value)
{
    new_ = new_value;

    return *this;
}

template <typename T>
inline
replace<T>& replace<T>::in(vector<T>& v)
{
    // v_ = v;
    v_ = &v;
    // std::cout << *v_ <<std::endl;

    return *this;
}

template <typename T>
inline
replace<T>& replace<T>::precision(T precision)
{
    precision_ = precision;

    return *this;
}

template <typename T>
inline
void replace<T>::run() const
{
    if (ney::config.target == Intel)
    {   
        if (is_integer_)
        {
            for (int i = v_->from(); i < v_->to(); i += v_->stride())
            {
                if ((*v_)[i] == old_)
                    (*v_)[i] = new_;
            }
        }
        else
        {
            for (int i = v_->from(); i < v_->to(); i += v_->stride())
            {
                if ((*v_)[i] > (old_ - precision_) && (*v_)[i] < (old_ + precision_))
                    (*v_)[i] = new_;
            }
        }
    }
    else if (ney::config.target == GPU)
    {

    }
}
