#include <iostream>
#include "../include/ney/ney.hpp"

//!

int main (int argc, char** argv)
{
    std::cout << "\n\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;
    int P = 10;

    ney::vector<double> x = ney::new_vector(10);
    ney::vector<double> y = ney::new_vector(10);
    ney::vector<double> m = ney::new_vector(10);


    s = ney::random<double>(x).min(0).max(10);
    s = ney::random<double>(y).min(0).max(10);
    s = ney::random<double>(m).min(0).max(1);

    

    // print time

    ney::clock::get().end().print();

    return 0;
}
