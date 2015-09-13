#include "../main.hpp"
#include "../replace.hpp"
#include "../vector.hpp"

template <typename T>
inline replace<T>::
replace(T old_value) : old_(old_value), v_(NULL)
{
    this->detect_data_type();
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
    v_ = &v;

    return *this;
}

template <typename T>
inline
void replace<T>::run() const
{
    if (ney::config.target == Intel)
    {
        if (v_->stride() == 1)
        {
            if (this->is_integer_)
            {
                #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                #pragma simd
                // #pragma vector aligned
                for (int i = v_->from(); i < v_->to(); i++)
                {
                    if ((*v_)[i] == old_)
                        (*v_).set(i, new_);
                }
            }
            else
            {
                #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                #pragma simd
                // #pragma vector aligned
                for (int i = v_->from(); i < v_->to(); i++)
                {
                    if (fabs((*v_)[i] - old_) < this->precision_)
                        (*v_).set(i, new_);
                }
            }
        }
        else
        {
            if (this->is_integer_)
            {
                #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                #pragma simd
                // #pragma vector aligned
                for (int i = v_->from(); i < v_->to(); i += v_->stride())
                {
                    if ((*v_)[i] == old_)
                        (*v_).set(i, new_);
                }
            }
            else
            {
                #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                #pragma simd
                // #pragma vector aligned
                for (int i = v_->from(); i < v_->to(); i += v_->stride())
                {
                    if (fabs((*v_)[i] - old_) < this->precision_)
                        (*v_).set(i, new_);
                }
            }
        }
    }
    #if CC_CUDA
    else if (ney::config.target == GPU)
    {
        ney::gpu::replace<T>(*v_, old_, new_);
    }
    #endif
}
