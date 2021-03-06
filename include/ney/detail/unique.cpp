#include "../main.hpp"
#include "../unique.hpp"

// #include "../vector.hpp"

template <typename T>
inline unique<T>::
unique(vector<T>& v) : out_(NULL), v_(v)
{
    this->detect_data_type();
}

template <typename T>
inline
void unique<T>::run() const
{
    if (ney::config.target == Intel)
    {
        // a little hack: status class is unknown at this point (by some compilers...)

        ney::sort<T>(v_).run();

        int j = 0;
        v_.set(0, v_[v_.from()]);

        if (v_.stride() == 1)
        {
            if (this->is_integer_)
            {
                for (int i = v_.from() + v_.stride(); i < v_.to(); i++)
                {
                    if (v_[i] != v_[j])
                    {
                        v_.set(++j, v_[i]);
                    }
                }

                v_.reset();
                v_.to(j + 1);
            }
            else
            {
                for (int i = v_.from() + v_.stride(); i < v_.to(); i++)
                {
                    if (fabs(v_[i] - v_[j]) >= this->precision_)
                    {
                        v_.set(++j, v_[i]);
                    }
                }

                v_.reset();
                v_.to(j + 1);
            }
        }
        else
        {
            if (this->is_integer_)
            {
                for (int i = v_.from() + v_.stride(); i < v_.to(); i += v_.stride())
                {
                    if (v_[i] != v_[j])
                    {
                        v_.set(++j, v_[i]);
                    }
                }

                v_.reset();
                v_.to(j + 1);
            }
            else
            {
                for (int i = v_.from() + v_.stride(); i < v_.to(); i += v_.stride())
                {
                    if (fabs(v_[i] - v_[j]) >= this->precision_)
                    {
                        v_.set(++j, v_[i]);
                    }
                }

                v_.reset();
                v_.to(j + 1);
            }
        }
    }
    #if CC_CUDA
    else if (ney::config.target == GPU)
    {
        int size = ney::gpu::unique<T>(v_);
        v_.to(size);
    }
    #endif
}
