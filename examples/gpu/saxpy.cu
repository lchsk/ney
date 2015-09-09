#include <iostream>
#include "../../include/ney/ney.hpp"

//! Computes Y = a * X + Y, where X, Y - vectors, a - scalar

int main (int argc, char** argv)
{
    std::cout << "\nSaxpy: Y = a * X + Y\n\n";

    ney::config.target = ney::GPU;
    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    ney::vector<int> X = ney::new_vector().size(10);
    ney::vector<int> Y = ney::new_vector().size(10);
    int a = 2;

    s = ney::random<int>(X).min(0).max(10);
    s = ney::random<int>(Y).min(0).max(10);

    std::cout << "scalar a: " << a << "\n";
    std::cout << "X: \n" << X << "\n";
    std::cout << "Y: \n" << Y << "\n";

    s = ney::apply<int>(ney::operation::mul).vector1(X).value(a);
    s = ney::apply<int>(ney::operation::add).vector1(Y).vector2(X);

    std::cout << "result: \n" << Y << "\n";

    // print time

    ney::clock::get().end().print();

    return 0;
}
