#include "../main.hpp"
#include "../swap.hpp"
#include "../vector.hpp"

template <typename T>
inline swap<T>::
swap() : v1_(NULL), v2_(NULL)
{
}

template <typename T>
inline
swap<T>& swap<T>::vector1(vector<T>& v)
{
    v1_ = &v;

    return *this;
}

template <typename T>
inline
swap<T>& swap<T>::vector2(vector<T>& v)
{
    v2_ = &v;

    return *this;
}

template <typename T>
inline
void swap<T>::run() const
{
    if (ney::config.target == Intel)
    {
        if (this->v2_ == NULL)
        {
            // swap elements in the first vector

            int d = floor((v1_->to() - v1_->from()) / 2.0);

            for (int i = v1_->from(); i < d; i += v1_->stride())
                std::swap((*v1_)[i + d], (*v1_)[i]);
        }
        else
        {
            // swap elements in two vectors

            for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                std::swap((*v1_)[i], (*v2_)[i]);
        }
    }
    else if (ney::config.target == GPU)
    {

    }
}