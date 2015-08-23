#include <iostream>
#include "../include/ney/ney.hpp"

#define SAMPLES 1000000.0
#define PI 3.14159265359

// It is a user-defined function. Returns true if point (x, y) is inside a circle

bool inside_circle(const double* x, const double* y)
{
    double dist = sqrt(*x * *x + *y * *y);

    if (dist < 1.0)
        return true;
    else
        return false;
}

//! Calculation of Pi Using the Monte Carlo Method

int main (int argc, char** argv)
{
    std::cout << "\nCalculation of Pi Using the Monte Carlo Method\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;

    // vectors holding x and y coordinates

    ney::vector<double> x = ney::new_vector().size(SAMPLES);
    ney::vector<double> y = ney::new_vector().size(SAMPLES);

    // vector holding comparison output

    ney::vector<bool> o = ney::new_vector().size(SAMPLES);

    // take SAMPLES random guesses

    s = ney::random<double>(x).min(0).max(1);
    s = ney::random<double>(y).min(0).max(1);

    // run comparison using a user-defined function

    s = ney::compare<double>().vector1(x).vector2(y).output(o).condition(inside_circle);

    int count = 0;

    // count how many guesses are inside a circle

    s = ney::count<bool>(true).in(o).output(count);

    // use a formula to estimate PI

    double ESTIMATED_PI = 4.0 * count / SAMPLES;

    // print estimted value of PI and an errorw

    std::cout << std::fixed;
    std::cout << "Number of samples: " << SAMPLES << std::endl;
    std::cout << std::setprecision(7);
    std::cout << "Estimated PI: " << ESTIMATED_PI << std::endl;
    std::cout << "Error: " << ESTIMATED_PI - PI << std::endl << std::endl;

    // print time

    ney::clock::get().end().print();

    return 0;
}
