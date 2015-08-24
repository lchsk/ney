#ifndef NEY_TIMER_HPP_
#define NEY_TIMER_HPP_

#include "time_engine.hpp"

NEY_NS_BEGIN

//! Class used to time any part of the program. A user can create any number of `timer`s

class timer
{
    public:

        //! Constructor takes no parameters

        timer();

        ~timer(){};

        //! Start timing

        timer& start();

        //! End timing

        timer& end();

        //! Set number of decimal places used when printing

        timer& precision(unsigned p);

        //! Returns current timer precision

        unsigned precision() const;

        //! print to standard output

        timer& print();

        //! Return time between `start()` and `end()` (in seconds)

        double time() const;

    private:
        time_engine engine_;
        unsigned decimal_places_;
};

#include "detail/timer.cpp"

NEY_NS_END

#endif
