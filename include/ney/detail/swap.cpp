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

            if (v1_->stride() == 1)
            {
                if (this->cond_ == NULL)
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma ivdep
                    #pragma vector aligned
                    for (int i = v1_->from(); i < d; i++)
                    {
                        T tmp = (*v1_)[i + d];
                        v1_->set(i + d, (*v1_)[i]);
                        v1_->set(i, tmp);
                        // std::swap((*v1_)[i + d], (*v1_)[i]);

                    }
                }
                else
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma vector aligned
                    for (int i = v1_->from(); i < d; i++)
                    {
                        T a, b;

                        a = (*v1_)[i];
                        b = (*v1_)[i + d];

                        // if (this->cond_(&(*v1_)[i], &(*v1_)[i + d]))
                        if (this->cond_(&a, &b))
                        {
                            // T tmp = (*v1_)[i + d];
                            v1_->set(i + d, a);
                            v1_->set(i, b);
                        }
                            // std::swap((*v1_)[i + d], (*v1_)[i]);
                    }
                }
            } // end stride == 1
            else
            {
                if (this->cond_ == NULL)
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma ivdep
                    #pragma vector aligned
                    for (int i = v1_->from(); i < d; i += v1_->stride())
                    {
                        T tmp = (*v1_)[i + d];
                        v1_->set(i + d, (*v1_)[i]);
                        v1_->set(i, tmp);
                        // std::swap((*v1_)[i + d], (*v1_)[i]);

                    }
                }
                else
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma vector aligned
                    for (int i = v1_->from(); i < d; i += v1_->stride())
                    {
                        T a, b;

                        a = (*v1_)[i];
                        b = (*v1_)[i + d];

                        // if (this->cond_(&(*v1_)[i], &(*v1_)[i + d]))
                        if (this->cond_(&a, &b))
                        {
                            // T tmp = (*v1_)[i + d];
                            v1_->set(i + d, a);
                            v1_->set(i, b);
                        }
                            // std::swap((*v1_)[i + d], (*v1_)[i]);
                    }
                }
            }

        }
        else
        {
            // swap elements in two vectors

            if (v1_->stride() == 1)
            {
                if (this->cond_ == NULL)
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma ivdep
                    #pragma vector aligned
                    for (int i = v1_->from(); i < v1_->to(); i++)
                    {
                        T tmp = (*v1_)[i];
                        v1_->set(i, (*v2_)[i]);
                        v2_->set(i, tmp);
                    }
                        // std::swap((*v1_)[i], (*v2_)[i]);
                }
                else
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma ivdep
                    #pragma vector aligned
                    for (int i = v1_->from(); i < v1_->to(); i++)
                    {
                        T a, b;
                        a = (*v1_)[i];
                        b = (*v2_)[i];

                        if (this->cond_(&a, &b))
                        // if (this->cond_(&(*v1_)[i], &(*v2_)[i]))
                        {
                            T tmp = (*v1_)[i];
                            v1_->set(i, (*v2_)[i]);
                            v2_->set(i, tmp);
                        }
                            // std::swap((*v1_)[i], (*v2_)[i]);
                    }
                }
            } // end stride == 1
            else
            {
                if (this->cond_ == NULL)
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma ivdep
                    #pragma vector aligned
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                    {
                        T tmp = (*v1_)[i];
                        v1_->set(i, (*v2_)[i]);
                        v2_->set(i, tmp);
                    }
                        // std::swap((*v1_)[i], (*v2_)[i]);
                }
                else
                {
                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    #pragma simd
                    #pragma ivdep
                    #pragma vector aligned
                    for (int i = v1_->from(); i < v1_->to(); i += v1_->stride())
                    {
                        T a, b;
                        a = (*v1_)[i];
                        b = (*v2_)[i];

                        if (this->cond_(&a, &b))
                        // if (this->cond_(&(*v1_)[i], &(*v2_)[i]))
                        {
                            T tmp = (*v1_)[i];
                            v1_->set(i, (*v2_)[i]);
                            v2_->set(i, tmp);
                        }
                            // std::swap((*v1_)[i], (*v2_)[i]);
                    }
                }
            }
        }
    }
}
