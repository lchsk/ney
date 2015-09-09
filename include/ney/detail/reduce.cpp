#include "../main.hpp"
#include "../reduce.hpp"
#include "../vector.hpp"

template <typename T>
inline reduce<T>::
reduce(vector<T>& v) : v_(v), init_value_(0), output_(NULL), operation_(operation::none)
{
}

template <typename T>
inline
reduce<T>& reduce<T>::use(operation::operation_t t)
{
    operation_ = t;

    return *this;
}

template <typename T>
inline
reduce<T>& reduce<T>::output(T& output)
{
    output_ = &output;

    return *this;
}

template <typename T>
inline
reduce<T>& reduce<T>::init(T init_value)
{
    init_value_ = init_value;

    return *this;
}

template <typename T>
inline
void reduce<T>::run() const
{
    *output_ = init_value_;

    T r = *output_;

    if (ney::config.target == Intel)
    {
        #if USE_MIC

        if (OFFLOAD_FORCE || (OFFLOAD_OK && this->v_.size() > 2000))
        {
            this->offloaded_ = true;
            this->set_worksharing(&v_);

            T r1, r2;
            r1 = r2 = 0;
            int from1 = this->from1;
            int to1 = this->to1;
            int stride = v_.stride();

            if (stride == 1)
            {
                if (operation_ == operation::add)
                {
                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_.raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(r1)
                        	{
                                #pragma omp parallel for schedule(static) reduction(+:r)
                                for (int i = from1; i < to1; i++)
                                {
                                    r1 += raw[i];
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) reduction(+:r)  num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i++)
                            {
                                r2 += v_[i];
                            }
                        }
                    }

                    r = r + r1 + r2;
                }
                else if (operation_ == operation::mul)
                {
                    r1 = r2 = init_value_;

                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_.raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(r1)
                        	{
                                #pragma omp parallel for schedule(static) reduction(*:r)
                                for (int i = from1; i < to1; i++)
                                {
                                    r1 *= raw[i];
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) reduction(*:r)  num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i++)
                            {
                                r2 *= v_[i];
                            }
                        }
                    }

                    r = r1 * r2;
                }
            } // end stride == 1
            else
            {
                if (operation_ == operation::add)
                {
                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_.raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(r1)
                        	{
                                #pragma omp parallel for schedule(static) reduction(+:r)
                                for (int i = from1; i < to1; i += stride)
                                {
                                    r1 += raw[i];
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) reduction(+:r)  num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i += stride)
                            {
                                r2 += v_[i];
                            }
                        }
                    }

                    r = r + r1 + r2;
                }
                else if (operation_ == operation::mul)
                {
                    r1 = r2 = init_value_;

                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            T* raw = v_.raw();

                            #pragma offload target(mic) in(raw:length(to1)) in(from1, to1, stride, value_) inout(r1)
                        	{
                                #pragma omp parallel for schedule(static) reduction(*:r)
                                for (int i = from1; i < to1; i += stride)
                                {
                                    r1 *= raw[i];
                                }
                        	}
                        }
                        #pragma omp section
                        {
                            // running on the host

                            #pragma omp parallel for schedule(static) reduction(*:r)  num_threads(NUM_THREADS)
                            for (int i = this->from2; i < this->to2; i += stride)
                            {
                                r2 *= v_[i];
                            }
                        }
                    }

                    r = r1 * r2;
                }
            }
        }

        #endif

        if ( ! this->offloaded_)
        {
            if (v_.stride() == 1)
            {
                if (operation_ == operation::add)
                {
                    #pragma omp parallel for schedule(static) reduction(+:r) num_threads(NUM_THREADS)
                    for (int i = v_.from(); i < v_.to(); i++)
                    {
                        r += v_[i];
                    }
                }
                else if (operation_ == operation::mul)
                {
                    #pragma omp parallel for schedule(static) reduction(*:r) num_threads(NUM_THREADS)
                    for (int i = v_.from(); i < v_.to(); i++)
                    {
                        r *= v_[i];
                    }
                }
            }
            else
            {
                if (operation_ == operation::add)
                {
                    #pragma omp parallel for schedule(static) reduction(+:r) num_threads(NUM_THREADS)
                    for (int i = v_.from(); i < v_.to(); i += v_.stride())
                    {
                        r += v_[i];
                    }
                }
                else if (operation_ == operation::mul)
                {
                    #pragma omp parallel for schedule(static) reduction(*:r) num_threads(NUM_THREADS)
                    for (int i = v_.from(); i < v_.to(); i += v_.stride())
                    {
                        r *= v_[i];
                    }
                }
            }
        }

        *output_ = r;
    }
    #if CC_CUDA
    else if (ney::config.target == GPU)
    {
        *output_ = ney::gpu::reduce<T>(v_, init_value_, operation_);
    }
    #endif
}
