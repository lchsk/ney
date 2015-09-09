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
        #if USE_MIC
        if (OFFLOAD_FORCE || (OFFLOAD_OK && this->v_->size() > 2000))
        {
            this->offloaded_ = true;
            this->set_worksharing(v_);

            T c1, c2;
            c1 = c2 = 0;
            int from1 = this->from1;
            int to1 = this->to1;
            int stride = v_->stride();

            if (stride == 1)
            {
                if (this->is_integer_)
                {
                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_->raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(c1)
                        	{
                                #pragma omp parallel for schedule(static)
                                for (int i = from1; i < to1; i ++)
                                {
                                    if (raw[i] == value_)
                                        #pragma omp atomic
                                        c1++;
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i ++)
                            {
                                if ((*v_)[i] == value_)
                                    #pragma omp atomic
                                    c2++;
                            }
                        }
                    }

                    *count_ = c1 + c2;
                }
                else
                {
                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_->raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(c1)
                        	{
                                #pragma omp parallel for schedule(static)
                                for (int i = from1; i < to1; i++)
                                {
                                    if (fabs(raw[i] - value_) < this->precision_)
                                        #pragma omp atomic
                                        c1++;
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i++)
                            {
                                if (fabs((*v_)[i] - value_) < this->precision_)
                                    #pragma omp atomic
                                    c2++;
                            }
                        }
                    }

                    *count_ = c1 + c2;
                }
            } // end stride == 1
            else
            {
                if (this->is_integer_)
                {
                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_->raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(c1)
                        	{
                                #pragma omp parallel for schedule(static)
                                for (int i = from1; i < to1; i += stride)
                                {
                                    if (raw[i] == value_)
                                        #pragma omp atomic
                                        c1++;
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i += stride)
                            {
                                if ((*v_)[i] == value_)
                                    #pragma omp atomic
                                    c2++;
                            }
                        }
                    }

                    *count_ = c1 + c2;
                }
                else
                {
                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_->raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(c1)
                        	{
                                #pragma omp parallel for schedule(static)
                                for (int i = from1; i < to1; i += stride)
                                {
                                    if (fabs(raw[i] - value_) < this->precision_)
                                        #pragma omp atomic
                                        c1++;
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i += stride)
                            {
                                if (fabs((*v_)[i] - value_) < this->precision_)
                                    #pragma omp atomic
                                    c2++;
                            }
                        }
                    }
                    *count_ = c1 + c2;
                }
            }
        }
        #endif

        if ( ! this->offloaded_)
        {
            // No MIC features

            if (v_->stride() == 1)
            {
                if (this->is_integer_)
                {
                    // cannot vectorise it

                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    for (int i = v_->from(); i < v_->to(); i++)
                    {
                        if ((*v_)[i] == value_)
                            #pragma omp atomic
                            (*count_)++;
                    }
                }
                else
                {
                    // cannot vectorise it

                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    for (int i = v_->from(); i < v_->to(); i++)
                    {
                        if (fabs((*v_)[i] - value_) < this->precision_)
                            #pragma omp atomic
                            (*count_)++;
                    }
                }
            } // end stride == 1
            else
            {
                if (this->is_integer_)
                {
                    // cannot vectorise it

                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
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

                    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
                    for (int i = v_->from(); i < v_->to(); i += v_->stride())
                    {
                        if (fabs((*v_)[i] - value_) < this->precision_)
                            #pragma omp atomic
                            (*count_)++;
                    }
                }
            }


        }

    }
    #if CC_CUDA
    else if (ney::config.target == GPU)
    {
        *count_ = ney::gpu::count<T>(*v_, value_);
    }
    #endif
}
