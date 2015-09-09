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
    use_scalar_(false),
    use_d_value(false)
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
    use_scalar_(false),
    use_d_value(false)
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
apply<T>& apply<T>::d_value(double value)
{
    use_d_value = true;
    d_value_ = value;

    return *this;
}

template <typename T>
inline
void apply<T>::run() const
{
    if (output_ == NULL)
        output_ = v1_;

    if (ney::config.target == Intel)
    {
        // Use case 1
        // if (f_ != function::none)
        // {
        if (f_ == function::sine)
        {
            if (v1_->stride() == 1)
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i++)
                {
                    (*output_).set(i, sin((*v1_)[i]));
                }
            }
            else
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                {
                    (*output_).set(i, sin((*v1_)[i]));
                }
            }

        }
        else if (f_ == function::cosine)
        {
            if (v1_->stride() == 1)
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i++)
                {
                    (*output_).set(i, cos((*v1_)[i]));
                }
            }
            else
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                {
                    (*output_).set(i, cos((*v1_)[i]));
                }
            }

        }
        else if (f_ == function::lower)
        {
            if (v1_->stride() == 1)
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i++)
                {
                    if ((*v1_)[i] >= 'A' && (*v1_)[i] <= 'Z')
                        (*output_).set(i, (*v1_)[i] + 32);
                }
            }
            else
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                {
                    if ((*v1_)[i] >= 'A' && (*v1_)[i] <= 'Z')
                        (*output_).set(i, (*v1_)[i] + 32);
                }
            }

        }
        else if (f_ == function::upper)
        {
            if (v1_->stride() == 1)
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i++)
                {
                    if ((*v1_)[i] >= 'a' && (*v1_)[i] <= 'z')
                        (*output_).set(i, (*v1_)[i] - 32);
                }
            }
            else
            {
                #pragma omp parallel for schedule(static)
                #pragma simd
                for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                {
                    if ((*v1_)[i] >= 'a' && (*v1_)[i] <= 'z')
                        (*output_).set(i, (*v1_)[i] - 32);
                }
            }

        }

        else if (v1_ != NULL && v2_ != NULL)
        {
            if (use_scalar_)
            {
                // Use case 3

                if (op_ == operation::add)
                {
                    if (v1_->stride() == 1)
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i++)
                        {
                            (*output_).set(i, ((*v1_)[i] + (*v2_)[i]) + value_);
                        }
                    }
                    else
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        {
                            (*output_).set(i, ((*v1_)[i] + (*v2_)[i]) + value_);
                        }
                    }

                }
                else if (op_ == operation::mul)
                {
                    if (v1_->stride() == 1)
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i++)
                        {
                            (*output_).set(i, ((*v1_)[i] * (*v2_)[i]) + value_);
                        }
                    }
                    else
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        {
                            (*output_).set(i, ((*v1_)[i] * (*v2_)[i]) + value_);
                        }
                    }

                }
            }
            else
            {
                // Use case 2

                if (op_ == operation::add)
                {
                    if (v1_->stride() == 1)
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i++)
                            (*output_).set(i, (*v1_)[i] + (*v2_)[i]);
                    }
                    else
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                            (*output_).set(i, (*v1_)[i] + (*v2_)[i]);
                    }

                }
                else if (op_ == operation::mul)
                {
                    if (v1_->stride() == 1)
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i++)
                            (*output_).set(i, (*v1_)[i] * (*v2_)[i]);
                    }
                    else
                    {
                        #pragma omp parallel for schedule(static)
                        #pragma simd
                        for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                            (*output_).set(i, (*v1_)[i] * (*v2_)[i]);
                    }

                }
            }
        }
        // Use case 4
        else if (use_scalar_ && v1_ != NULL)
        {
            if (op_ == operation::add)
            {
                if (v1_->stride() == 1)
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i++)
                        (*output_).set(i, (*v1_)[i] + value_);
                }
                else
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        (*output_).set(i, (*v1_)[i] + value_);
                }

            }
            else if (op_ == operation::mul)
            {
                if (v1_->stride() == 1)
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i++)
                        (*output_).set(i, (*v1_)[i] * value_);
                }
                else
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        (*output_).set(i, (*v1_)[i] * value_);
                }

            }
        }
        // use ney::value<T1>
        else if (use_d_value && v1_ != NULL)
        {
            if (op_ == operation::add)
            {
                if (v1_->stride() == 1)
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i++)
                        (*output_).set(i, (*v1_)[i] + d_value_);
                }
                else
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        (*output_).set(i, (*v1_)[i] + d_value_);
                }

            }
            else if (op_ == operation::mul)
            {
                if (v1_->stride() == 1)
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i++)
                        (*output_).set(i, (*v1_)[i] * d_value_);
                }
                else
                {
                    #pragma omp parallel for schedule(static)
                    #pragma simd
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                        (*output_).set(i, (*v1_)[i] * d_value_);
                }

            }
        }
    }
    #if CC_CUDA
    else if (ney::config.target == GPU)
    {
        if (f_ != ney::function::none)
            ney::gpu::apply<T>(*output_, *v1_, f_, output_ == v1_);
        else if(v1_ != NULL && v2_ != NULL && use_scalar_)
        {
            ney::gpu::apply<T>(*output_, *v1_, *v2_, value_, op_, output_ == v1_);
        }
        else if(v1_ != NULL && v2_ != NULL  && ! use_scalar_)
        {
            ney::gpu::apply<T>(*output_, *v1_, *v2_, op_, output_ == v1_);
        }
        else if (use_scalar_ && v1_ != NULL)
        {
            ney::gpu::apply<T>(*output_, *v1_, value_, op_, output_ == v1_);
        }
        else if (use_d_value && v1_ != NULL)
        {
            ney::gpu::apply<T>(*output_, *v1_, use_d_value, d_value_, op_, output_ == v1_);
        }

    }
    #endif
}
