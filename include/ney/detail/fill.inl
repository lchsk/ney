#include "../fill.hpp"
#include "../vector.hpp"

template <class T>
inline fill<T>::
// fill(const vector<T>& vec)
fill(vector<T>& v) : out(v)
{
    // for (int i = 0; i < 10; i++)
    // {
    //     v.data_[i] = 2;
    // }
}

template <typename T>
inline
fill<T>& fill<T>::run() const
{

}
