#include "../main.hpp"
#include "../clock.hpp"

clock& clock::start()
{
    engine_.start();
    return *this;
}

clock& clock::end()
{
    engine_.end();

    return *this;
}

clock& clock::precision(unsigned p)
{
    decimal_places_ = p;

    return *this;
}

unsigned clock::precision() const
{
    return decimal_places_;
}

double inline clock::time() const
{
    return engine_.time();
}

clock& clock::print()
{
    std::cout << "clock(total time: " << std::setiosflags(std::ios::fixed) << std::setprecision(this->decimal_places_) << engine_.time() << " s)" << std::endl;

    return *this;
}

std::ostream& operator<<(std::ostream& s, clock& t)
{
    t.print();

    return s;
}
