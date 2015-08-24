#include "../main.hpp"
#include "../sort.hpp"
#include "../vector.hpp"

template <typename T>
inline sort<T>::
sort(vector<T>& v) : a_(v)
{
    #if ALIGNMENT_OK
        b_ = (T*) MALLOC (sizeof (T*) * a_.size(), ALIGN);
    #else
        b_ = (T*) MALLOC (sizeof (T*) * a_.size());
    #endif
}

template <typename T>
inline sort<T>::
~sort()
{
    if (b_ != NULL)
    {
        FREE (b_);
        b_ = NULL;
    }
}

template <typename T>
void sort<T>::merge_sort(int low, int high) const
{
    int mid;

    if(low < high)
    {
        mid = low + (high - low) / 2;

        // #pragma omp parallel sections
        {
            // #pragma omp section
            merge_sort(low, mid);

            // #pragma omp section
            merge_sort(mid + 1, high);
        }

        merge(low, mid, high);
    }
}

template <typename T>
void sort<T>::merge(int low, int mid, int high) const
{
    int h, i, j, k;
    h = low;
    i = low;
    j = mid + 1;

    while ((h <= mid) && (j <= high))
    {
        if(a_[h] <= a_[j])
        {
            (b_)[i] = a_[h];
            h++;
        }
        else
        {
            (b_)[i] = a_[j];
            j++;
        }
        i++;
    }

    if(h > mid)
    {
        #pragma simd
        for(k = j; k <= high; k++)
        {
            (b_)[i] = a_[k];
            i++;
        }
    }
    else
    {
        #pragma simd
        for(k = h; k <= mid; k++)
        {
            (b_)[i] = a_[k];
            i++;
        }
    }

    #pragma simd
    for(k = low; k <= high; k++)
        a_[k] = (b_)[k];
}

template <typename T>
inline
void sort<T>::run() const
{
    if (ney::config.target == Intel)
    {
        merge_sort(0, a_.size() - 1);
    }
}
