#define USE_MIC FALSE
#include <iostream>
#include "../../include/ney/ney.hpp"

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
    }

    ney::config.target = ney::Intel;

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    int r;

    ney::vector<int> x2 = ney::new_vector().size(size);

    s = ney::fill<int>(x2).value(1).time();
    std::cout << s << "\n";

    s = ney::reduce<int>(x2).use(ney::operation::add).output(r).time();
    std::cout << s << "\n";

    ney::vector<int> x3 = ney::new_vector().size(100000000);

    s = ney::fill<int>(x3).value(1).time();
    std::cout << s << "\n";

    s = ney::reduce<int>(x3).use(ney::operation::add).output(r).time();
    std::cout << s << "\n";

    // print time

    ney::clock::get().end().print();

    return 0;
}
