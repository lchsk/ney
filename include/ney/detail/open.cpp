#include "../main.hpp"
#include "../open.hpp"
#include "../vector.hpp"

template <typename T>
inline open<T>::
open(std::string path) :
    path_(path),
    v_(NULL),
    parallel_(false),
    as_text_(false)
{
    this->detect_data_type();
}

template <typename T>
inline
open<T>& open<T>::output(vector<T>& v)
{
    v_ = &v;

    return *this;
}

template <typename T>
inline
open<T>& open<T>::as_text()
{
    as_text_ = true;

    return *this;
}

template <typename T>
inline
void open<T>::run() const
{
    // if (ney::config.target == Intel)
    {
        if (as_text_ && ! parallel_)
        {
            FILE* f = fopen(path_.c_str(), "rb");

            fseek(f, 0, SEEK_END);
            long size = ftell(f);
            fseek(f, 0, SEEK_SET);

            #if CC_CUDA
                if (ney::config.target == GPU)
                {
                    *v_ = new_vector().size(size);
                    char* tmp = new char[size];
                    int res = fread(tmp, size, 1, f);

                    for (int i = 0; i < size; i++)
                    {
                        *v_ << tmp[i];
                    }
                }
            #else
                if (ney::config.target == Intel)
                {
                    *v_ = new_vector().size(size);
                    fread(v_->data_, size, 1, f);
                }


            #endif

            fclose(f);
        }
        else if ( ! as_text_ && ! parallel_)
        {
            std::ifstream f(path_.c_str(), std::ios_base::in);

            long size = std::distance(std::istream_iterator<T>(f), std::istream_iterator<T>());

            f.clear();
            f.seekg (0, f.beg);

            *v_ = new_vector().size(size);

            T a;

            while (f >> a)
            {
                *v_ << a;
            }

            f.close();
        }
    }
}
