#include "../main.hpp"
#include "../apply.hpp"
#include "../vector.hpp"

template <typename T>
inline apply<T>::
apply(operation::operation_t op) : 
    op_(op), 
    f_(function::none),
    output_(NULL),
    v1_(NULL),
    v2_(NULL),
    use_scalar_(false)
{
}

template <typename T>
inline apply<T>::
apply(function::function_t f) : 
    f_(f), 
    op_(operation::none),
    output_(NULL),
    v1_(NULL),
    v2_(NULL),
    use_scalar_(false)
{
}

template <typename T>
inline
apply<T>& apply<T>::vector1(vector<T>& v)
{
    v1_ = &v;

    return *this;
}

template <typename T>
inline
apply<T>& apply<T>::vector2(vector<T>& v)
{
    v2_ = &v;

    return *this;
}


template <typename T>
inline
apply<T>& apply<T>::output(vector<T>& v)
{
    output_ = &v;

    return *this;
}


template <typename T>
inline
apply<T>& apply<T>::value(T value)
{
    value_ = value;
    use_scalar_ = true;

    return *this;
}

template <typename T>
inline
void apply<T>::run() const
{
    if (ney::config.target == Intel)
    {   
        if (output_ == NULL)
            output_ = v1_;



        // Use case 1
        // if (f_ != function::none)
        // {
        if (f_ == function::sine)
        {
            for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
            {
                (*output_)[i] = sin((*v1_)[i]);
            }
        }
        else if (f_ == function::cosine)
        {
            for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
            {
                (*output_)[i] = cos((*v1_)[i]);
            }
        }

        
        else if (v1_ != NULL && v2_ != NULL)
        {
            if (use_scalar_)
            {
                // Use case 3

                if (op_ == operation::add)
                {
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                    {
                        (*output_)[i] = ((*v1_)[i] + (*v2_)[i]) + value_;
                    }
                }
                else if (op_ == operation::mul)
                {
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        (*output_)[i] = ((*v1_)[i] * (*v2_)[i]) + value_;
                }
            }
            else
            {
                // Use case 2

                if (op_ == operation::add)
                {
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        (*output_)[i] += (*v2_)[i];
                }
                else if (op_ == operation::mul)
                {
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        (*output_)[i] *= (*v2_)[i];
                }
            }
        }
        // Use case 4
        else if (use_scalar_ && v1_ != NULL)
        {   
            if (op_ == operation::add)
            {
                for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                    (*output_)[i] += value_;
            }
            else if (op_ == operation::mul)
            {
                for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                    (*output_)[i] *= value_;
            }
        }
        // }

    }
    else if (ney::config.target == GPU)
    {

    }
}