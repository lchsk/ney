#include "../main.hpp"
#include "../replace.hpp"
#include "../vector.hpp"

template <typename T>
inline replace<T>::
replace(T old_value) : old_(old_value)
{
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
    // v_ = v;
    v_ = &v;
    // std::cout << *v_ <<std::endl;

    return *this;
}

template <typename T>
inline
void replace<T>::run() const
{
    if (ney::config.target == Intel)
    {
        for (int i = v_->from(); i < v_->to(); i += v_->stride())
        {
            if ((*v_)[i] == old_)
                (*v_)[i] = new_;
        }
    }
    else if (ney::config.target == GPU)
    {

    }
}
