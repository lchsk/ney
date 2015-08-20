#include <iostream>
#include "../../include/ney/ney.hpp"

//! Bitonic sort implementation

void b_compare(ney::vector<int>& v, bool asc)
{
    ney::status s;

    if (asc)
        s = ney::swap<int>().vector1(v).condition(ney::condition::gt);
    else
        s = ney::swap<int>().vector1(v).condition(ney::condition::lt);
}

ney::vector<int> merge(ney::vector<int>& v, bool asc)
{
    int len = v.length();

    if (len <= 1)
        return v;
    else
    {
        b_compare(v, asc);

        ney::vector<int> first_(v.reset().to(len / 2));
        ney::vector<int> second_(v.reset().from(len / 2));

        ney::vector<int> first(merge(first_, asc));
        ney::vector<int> second(merge(second_, asc));

        return first + second;
    }
}

ney::vector<int> b_sort(ney::vector<int>& v, bool asc)
{
    int len = v.length();

    if (len <= 1)
        return v;
    else
    {
        ney::vector<int> first_(v.reset().to(len / 2));
        ney::vector<int> second_(v.reset().from(len / 2));

        ney::vector<int> first(b_sort(first_, true));
        ney::vector<int> second(b_sort(second_, false));

        ney::vector<int> fs = first + second;

        return merge(fs, asc);
    }
}

int main (int argc, char** argv)
{
    std::cout << "\nBitonic sort\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    // init vector

    ney::vector<int> v = ney::new_vector().size(8);
    v << 5 << 8 << 2 << 6 << 0 << -5 << 2 << 1;

    ney::vector<int> sorted;

    sorted = b_sort(v.reset(), true);

    std::cout << "ascending: " << sorted << "\n";

    sorted = b_sort(v.reset(), false);

    std::cout << "descending: " << sorted << "\n";

    // print time

    ney::clock::get().end().print();

    return 0;
}
