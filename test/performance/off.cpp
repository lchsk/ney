#define USE_MIC FALSE
#include <iostream>
#include "../../include/ney/ney.hpp"

#define TYPE double

int main (int argc, char** argv)
{
    std::cout << "\nOffloading\n\n";
    int size;

    if (argv[1] == NULL)
    {
        std::cerr << "usage: " << argv[0] << " <size>" << std::endl;
        return 1;
    }
    else
    {
        size = atoi(argv[1]);
    }

    ney::config.target = ney::Intel;

    ney::config.print();
    int c;
    TYPE r;

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    ney::vector<TYPE> x = ney::new_vector().size(size);

    s = ney::random<TYPE>(x).min(0).max(10).time();
    std::cout << s << "\n";

    std::cout << "reduce\n";
    s = ney::reduce<TYPE>(x).use(ney::operation::add).output(r).time();
    std::cout << s << "\n";
    std::cout << "offloaded: " << s.offloaded() << "\n";
    std::cout << size * 1e-9 / s.time() << " Gflops\n\n";

    std::cout << "count\n";
    s = ney::count<TYPE>(0.2).precision(2).in(x).output(c).time();
    std::cout << s << "\n";
    std::cout << "offloaded: " << s.offloaded() << "\n";
    std::cout << size * 1e-9 / s.time() << " Gcomparisons\n\n";


    // print time

    ney::clock::get().end().print();

    return 0;
}
