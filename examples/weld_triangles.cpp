#include <iostream>
#include "../include/ney/ney.hpp"

//!

int main (int argc, char** argv)
{
    std::cout << "\nWeld triangles\n\n";

    ney::config.print();

    // start clock

    ney::clock::get().start().precision(7);

    ney::status s;

    ney::vector<int> x = ney::new_vector().size(9);
    ney::vector<int> y = ney::new_vector().size(9);

    x << 0 << 1 << 0 << 1 << 1 << 0 << 1 << 2 << 1;
    y << 0 << 0 << 1 << 0 << 1 << 1 << 0 << 0 << 1;

    std::cout << "input triangles (x, y):\n" << x << y << "\n";

    s = ney::apply<int>(ney::operation::mul).vector1(x).value(10);
    s = ney::apply<int>(ney::operation::add).vector1(x).vector2(y);

    ney::vector<int> xy(x);

    std::cout << "triangles (x * 10 + y): \n" << x << "\n";

    s = ney::unique<int>(x);

    std::cout << "vertices: \n" << x;

    ney::vector<int> tmp = ney::new_vector().size(x[x.length() - 1]);

    for (int i = 0; i < x.length(); i++)
        tmp[x[i]] = i;

    // indices

    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            std::cout << "\ntriangle " << i / 3 << std::endl;

        int id = tmp[xy[i]];

        std::cout << id << " (" << xy[i] / 10 << ", " << xy[i] % 10 << ") ";
    }

    std::cout << std::endl;

    // print time

    ney::clock::get().end().print();

    return 0;
}
