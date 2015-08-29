#include <iostream>
#include "../include/ney/ney.hpp"

//! Bitonic sort implementation

#define dtype double

void b_compare(ney::vector<dtype>& v, bool asc)
{
    ney::status s;

    if (asc)
        s = ney::swap<dtype>().vector1(v).condition(ney::condition::gt);
    else
        s = ney::swap<dtype>().vector1(v).condition(ney::condition::lt);
}

ney::vector<dtype> merge(ney::vector<dtype> v, bool asc)
{
    int len = v.length();

    if (len <= 1)
        return v;
    else
    {
        b_compare(v, asc);

        ney::vector<dtype> first_ = v.reset().to(len / 2);
        ney::vector<dtype> second_ = v.reset().from(len / 2);

        ney::vector<dtype> first = merge(first_, asc);
        ney::vector<dtype> second = merge(second_, asc);

        return first + second;
    }
}

ney::vector<dtype> b_sort(ney::vector<dtype>& v, bool asc)
{
    int len = v.length();

    if (len <= 1)
        return v;
    else
    {
        ney::vector<dtype> first_ = v.reset().to(len / 2);
        ney::vector<dtype> second_ = v.reset().from(len / 2);

        ney::vector<dtype> first;
        ney::vector<dtype> second;

        #pragma omp parallel sections
        {
            #pragma omp section
            first = b_sort(first_, true);

            #pragma omp section
            second = b_sort(second_, false);
        }

        // ney::vector<dtype> first = b_sort(first_, true);
        // ney::vector<dtype> second = b_sort(second_, false);

        return merge(first + second, asc);
    }
}

int main (int argc, char** argv)
{
    std::cout << "\nBitonic sort\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    // init vector

    int size = 1 << 20;
    std::cout << "size: " << size << "\n";

    ney::vector<dtype> v = ney::new_vector().size(size);
    // v << 5 << 8 << 2 << 6 << 0 << -5 << 2 << 1;

    ney::status s;
    s = ney::random<dtype>(v).min(0).max(10);

    ney::vector<dtype> sorted;

    // s = ney::sort<dtype>(v);
    // s = ney::sort<dtype>(v);

    sorted = b_sort(v.reset(), true);

    // std::cout << "ascending: " << sorted << "\n";

    sorted = b_sort(v.reset(), false);

    // std::cout << "descending: " << sorted << "\n";

    // print time

    ney::clock::get().end().print();

    return 0;
}
