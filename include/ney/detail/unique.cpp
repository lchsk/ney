#include "../main.hpp"
#include "../unique.hpp"
#include "../vector.hpp"

template <typename T>
inline unique<T>::
unique(vector<T>& v) : out_(NULL), v_(v)
{
    this->detect_data_type();
}

// template <typename T>
// inline
// unique<T>& unique<T>::output(vector<T>& v)
// {
//     out_ = &v;
//
//     return *this;
// }

template <typename T>
inline
void unique<T>::run() const
{
    if (ney::config.target == Intel)
    {
        ney::status s = ney::sort<T>(v_);

        int j = 0;
        v_[0] = v_[v_.from()];

        if (this->is_integer_)
        {
            for (int i = v_.from() + v_.stride(); i < v_.to(); i += v_.stride())
            {
                if (v_[i] != v_[j])
                {
                    v_[++j] = v_[i];
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
                    v_[++j] = v_[i];
                }
            }

            v_.reset();
            v_.to(j + 1);
        }
    }
}
