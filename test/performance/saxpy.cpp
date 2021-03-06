#define USE_MIC FALSE
#include <iostream>
#include "../../include/ney/ney.hpp"

//! Computes Y = a * X + Y, where X, Y - vectors, a - scalar

int main (int argc, char** argv)
{
    std::cout << "\nSaxpy: Y = a * X + Y\n\n";
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
    ney::vector<int> X = ney::new_vector().size(size);
    ney::vector<int> Y = ney::new_vector().size(size);
    int a = 2;

    s = ney::random<int>(X).min(0).max(10).time();
    std::cout << s << "\n";
    s = ney::random<int>(Y).min(0).max(10).time();
    std::cout << s << "\n";

    // std::cout << "scalar a: " << a << "\n";
    // std::cout << "X: \n" << X << "\n";
    // std::cout << "Y: \n" << Y << "\n";

    s = ney::apply<int>(ney::operation::mul).vector1(X).value(a).time();
    std::cout << s << "\n";
    s = ney::apply<int>(ney::operation::add).vector1(Y).vector2(X).time();
    std::cout << s << "\n";

    // std::cout << "result: \n" << Y << "\n";

    // print time

    ney::clock::get().end().print();

    return 0;
}
