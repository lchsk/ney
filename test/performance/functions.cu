#define USE_MIC FALSE
#include <iostream>
#include "../../include/ney/ney.hpp"

#define TYPE double

int main (int argc, char** argv)
{
    int size;

    if (argv[1] == NULL)
    {
        std::cerr << "usage: " << argv[0] << " <size>" << std::endl;
        return 1;
    }
    else
    {
        size = atoi(argv[1]);
        std::cout << "<size> was set to " << argv[1] << std::endl << std::endl;
    }

    ney::config.target = ney::GPU;

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    TYPE r;
    int c;

    ney::vector<TYPE> x = ney::new_vector().size(size);
    ney::vector<TYPE> y = ney::new_vector().size(size);

    std::cout << "fill\n";
    s = ney::fill<TYPE>(x).value(1).time();
    std::cout << s << "\n";
    std::cout << size * 1e-9 / s.time() << " Gwrites\n\n";

    std::cout << "random\n";
    s = ney::random<TYPE>(x).min(0).max(1).time();
    std::cout << s << "\n";
    std::cout << size * 1e-9 / s.time() << " Gwrites\n\n";

    std::cout << "replace\n";
    s = ney::replace<TYPE>(0.1).with(0.2).in(x);
    std::cout << s << "\n";
    std::cout << size * 1e-9 / s.time() << " Gcomparisons\n\n";

    std::cout << "reduce\n";
    s = ney::reduce<TYPE>(x).use(ney::operation::add).output(r).time();
    std::cout << s << "\n";
    std::cout << size * 1e-9 / s.time() << " Gflops\n\n";

    std::cout << "count\n";
    s = ney::count<TYPE>(0.2).precision(2).in(x).output(c).time();
    std::cout << s << "\n";
    std::cout << size * 1e-9 / s.time() << " Gcomparisons\n\n";

    std::cout << "apply (v1 + v2)\n";
    s = ney::apply<TYPE>(ney::operation::add).vector1(x).vector2(y).time();
    std::cout << s << "\n";
    std::cout << size * 1e-9 / s.time() << " Gflops\n\n";

    std::cout << "sort\n";
    s = ney::sort<TYPE>(y).time();
    std::cout << s << "\n\n";

    std::cout << "unique\n";
    s = ney::unique<TYPE>(x).time();
    std::cout << s << "\n\n";

    // print time

    ney::clock::get().end().print();

    return 0;
}
