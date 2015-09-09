#include <iostream>
#include "../include/ney/ney.hpp"

//! Run Length Encoding

int main (int argc, char** argv)
{
    std::cout << "\nRun Length Encoding\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    ney::vector<int> v = ney::new_vector(100);

    s = ney::random<int>(v).min('a').max('z');
    ney::vector<int> v2(v);

    if (s.success())
    {
        std::cout << "Input:\n";

        for (int i = 0; i < v.length(); i++)
            std::cout << (char)v[i];

        std::cout << std::endl;

        s = ney::unique<int>(v);
        ney::vector<int> counts = ney::new_vector().size(v.length());

        for (int i = 0; i < v.length(); i++)
        {
            int tmp = counts[i];
            s = ney::count<int>(v[i]).in(v2).output(tmp);
            counts.set(i, tmp);
        }

        std::cout << std::endl << "encoded: " << std::endl;

        for (int i = 0; i < v.length(); i++)
        {
            std::cout << counts[i] << (char)v[i] << " ";
        }

        std::cout << std::endl;
    }
    else
    {
        std::cerr << "Error while generating input" << std::endl;
    }

    std::cout << std::endl;

    // print time

    ney::clock::get().end().print();

    return 0;
}
