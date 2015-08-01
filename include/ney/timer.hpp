#ifndef NEY_TIMER_HPP_
#define NEY_TIMER_HPP_

#include "time_engine.hpp"

NEY_NS_BEGIN

class timer
{
    public:
        timer();
        ~timer(){};

        timer& start();
        timer& end();
        timer& precision(unsigned p);
        timer& print();

        double time() const;

    private:
        time_engine engine_;
        unsigned decimal_places_;
};

#include "detail/timer.cpp"

NEY_NS_END

#endif
