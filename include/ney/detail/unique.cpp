#include "../main.hpp"
#include "../unique.hpp"
#include "../vector.hpp"

template <typename T>
inline unique<T>::
unique(vector<T>& v) : out_(NULL), v_(v)
{
    this->detect_data_type();
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
    // bool unique = true;
    // T value;
    // int new_i = 0;

    if (ney::config.target == Intel)
    {
        ney::status s = ney::sort<T>(v_);

        std::cout << v_ << std::endl;

        int j = 0;
        (*out_)[0] = v_[v_.from()];
        // T last = (*out_)[0];


        if (this->is_integer_)
        {
            for (int i = v_.from() + v_.stride(); i < v_.to(); i += v_.stride())
            {
                if (v_[i] != (*out_)[j])
                {
                    (*out_)[++j] = v_[i];
                }
            }
        }
        else
        {
            for (int i = v_.from() + v_.stride(); i < v_.to(); i += v_.stride())
            {
                if (fabs((*old_)[i] - v_[i]) < this->precision_)
                {
                    (*out_)[++j] = v_[i];
                }
            }

            // for (int i = v_->from(); i < v_->to(); i += v_->stride())
            // {
            //     if (fabs((*v_)[i] - old_) < this->precision_)
            //         (*v_)[i] = new_;
            // }
        }

        // for (int i = v_.from(); i < v_.to(); i += v_.stride())
        // {
        //     unique = true;
        //
        //     for (int j = out_->from(); j < out_->to(); j += out_->stride())
        //     {
        //         if (v_[i] == (*out_)[j])
        //         {
        //             // value = v_[i];
        //             unique = false;
        //         }
        //     }
        //
        //     if (unique)
        //         (*out_)[new_i++] = v_[i];
        // }
        //
        // std::cout << "len: " << new_i << "\n";

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
