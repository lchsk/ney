#include "../main.hpp"
#include "../timer.hpp"

timer::timer() : decimal_places_(DEFAULT_DECIMAL_PLACES)
{
}

timer& timer::start()
{
    engine_.start();
    return *this;
}

timer& timer::end()
{
    engine_.end();

    return *this;
}

timer& timer::precision(unsigned p)
{
    decimal_places_ = p;

    return *this;
}

double inline timer::time() const
{
    return engine_.time();
}

timer& timer::print()
{
    std::cout << "timer(total time: " 
            << std::setiosflags(std::ios::fixed)
            << std::setprecision(this->decimal_places_)
            << engine_.time()
            << " s)" << std::endl;

    return *this;
}

std::ostream& operator<<(std::ostream& s, timer& t)
{
    t.print();

    return s;
}