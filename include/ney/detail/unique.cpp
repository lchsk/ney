#include "../main.hpp"
#include "../unique.hpp"
#include "../vector.hpp"

template <typename T>
inline unique<T>::
unique(vector<T>& v) : out_(NULL), v_(v)
{
}

template <typename T>
inline
unique<T>& unique<T>::output(vector<T>& v)
{
    out_ = &v;

    return *this;
}

template <typename T>
inline
void unique<T>::run() const
{
    bool unique = true;
    T value;
    int new_i = 0;

    if (ney::config.target == Intel)
    {
        for (int i = v_.from(); i < v_.to(); i += v_.stride())
        {
            unique = true;

            for (int j = out_->from(); j < out_->to(); j += out_->stride())
            {
                if (v_[i] == (*out_)[j])
                {
                    // value = v_[i];
                    unique = false;
                }
            }

            if (unique)
                (*out_)[new_i++] = v_[i];
        }

        std::cout << "len: " << new_i << "\n";

    //     int i, j;
      //
    //     /* new length of modified array */
    //     int NewLength = 1;
      //
    //     for(i=1; i < v_.to(); i++)
    //     {
    //         for(j = 0; j < v_.to(); j++)
    //         {
    //             if(v_[i] == v_[j])
    //             {
    //                 std::cout << v_[i] << "\n";
    //                 break;
      //
    //             }
    //         }
      //
    //         /* if none of the values in index[0..j] of array is not same as array[i],
    //   then copy the current value to corresponding new position in array */
      //
    //         if (j == NewLength)
    //         {
    //             std::cout << "hej < " << j << "\n";
    //             v_[NewLength++] = v_[i];
      //
    //         }
    //     }
    }
    else if (ney::config.target == GPU)
    {

    }
}
