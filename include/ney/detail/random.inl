#include "../random.hpp"
#include "../vector.hpp"

template <typename T>
inline random<T>::
random(vector<T>& v) : out(v), min_(0), max_(RAND_MAX)
{
    // std::cout << msg;
    this->msg = "random";
}

// template <typename T>
// random<T>& random<T>::cast()
// {
//     return (random<T>&)*this;
//     // return &((random<T>)*this);
//     // return *dynamic_cast<random<T>&>(*this);
//     // random<T> t = static_cast<random<T> >(*this);
//     // return t;
// }

template <typename T>
inline random<T>& random<T>::min(T min)
{
    min_ = min;

    return *this;
}

template <typename T>
inline random<T>& random<T>::max(T max)
{
    max_ = max;

    return *this;
}

template <typename T>
inline
void random<T>::run() const
{
    if (ney::config.target == Intel)
    {
        for (int i = out.from(); i < out.to(); i += out.stride())
            out.data_[i] = min_ + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(max_-min_)));
            // out.data_[i] = (rand() % (max_ - min_) + min_);
    }
    else if (ney::config.target == GPU)
    {

    }
}
