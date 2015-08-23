#include "../main.hpp"
#include "../count.hpp"
#include "../vector.hpp"

template <typename T>
inline count<T>::
count(T value) : value_(value), count_(NULL), v_(NULL)
{
    this->detect_data_type();
}

template <typename T>
inline
count<T>& count<T>::in(vector<T>& v)
{
    v_ = &v;

    return *this;
}

template <typename T>
inline
count<T>& count<T>::output(int& output)
{
    count_ = &output;
    *count_ = 0;

    return *this;
}

template <typename T>
inline
void count<T>::run() const
{
    if (ney::config.target == Intel)
    {
        if (this->is_integer_)
        {
            // cannot vectorise it

            #pragma omp parallel for schedule(static)
            for (int i = v_->from(); i < v_->to(); i += v_->stride())
            {
                if ((*v_)[i] == value_)
                    #pragma omp atomic
                    (*count_)++;
            }
        }
        else
        {
            // cannot vectorise it

            #pragma omp parallel for schedule(static)
            for (int i = v_->from(); i < v_->to(); i += v_->stride())
            {
                if (fabs((*v_)[i] - value_) < this->precision_)
                    #pragma omp atomic
                    (*count_)++;
            }
        }
    }
    else if (ney::config.target == GPU)
    {

    }
}
