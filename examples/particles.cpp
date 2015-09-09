#include <iostream>
#include "../include/ney/ney.hpp"

//! Generates a number of randomly placed particles. In each step, particles are moved by some random value. If a particle reaches the centre of the box, it dies, and two new randmly placed particles are born.

#define BOX_W 10
#define BOX_H 10

bool is_inside(const double* x, const double* y)
{
    if (*x > 4.5 && *x < 5.5 && *y > 4.5 && *y < 5.5)
        return true;
    else
        return false;
}

int main (int argc, char** argv)
{
    std::cout << "\n\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;

    int max_particles = 100;
    int particles = 10;
    int steps = 10000;

    std::cout << "Initial parameters: \n";
    std::cout << "\tParticles: " << particles << "\n";
    std::cout << "\tSteps: " << steps << "\n";

    ney::vector<double> x = ney::new_vector(max_particles);
    ney::vector<double> y = ney::new_vector(max_particles);
    ney::vector<double> xd = ney::new_vector(max_particles);
    ney::vector<double> yd = ney::new_vector(max_particles);
    ney::vector<bool> o = ney::new_vector(max_particles);
    ney::vector<bool> alive = ney::new_vector(max_particles);

    s = ney::fill<bool>(alive.to(particles)).value(true);
    s = ney::random<double>(x.to(particles)).min(0).max(BOX_W);
    s = ney::random<double>(y.to(particles)).min(0).max(BOX_H);

    ney::vector<double> d = ney::new_vector(max_particles * max_particles);

    for (int i = 0; i < steps; i++)
    {
        s = ney::random<double>(xd.to(particles)).min(-1).max(1);
        s = ney::random<double>(yd.to(particles)).min(-1).max(1);

        s = ney::apply<double>(ney::operation::add).vector1(x.to(particles)).vector2(xd);
        s = ney::apply<double>(ney::operation::add).vector1(y.to(particles)).vector2(yd);

        s = ney::compare<double>().
            vector1(x.to(particles)).
            vector2(y.to(particles)).
            output(o.to(particles)).
            condition(is_inside);

        for (int j = 0; j < particles; j++)
        {
            if (o[j] && alive[j])
            {
                alive.set(j, false);

                x.set(particles, rand() % BOX_W);
                y.set(particles, rand() % BOX_H);

                particles++;

                x.set(particles, rand() % BOX_W);
                y.set(particles, rand() % BOX_H);

                particles++;
            }
        }
    }

    int count;
    s = ney::count<bool>(true).in(alive).output(count);

    std::cout << "After simulation:\n";
    std::cout << "\tParticles: " << particles << "\n";

    // print time

    ney::clock::get().end().print();

    return 0;
}
