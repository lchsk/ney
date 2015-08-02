#ifndef NEY_CLOCK_HPP_
#define NEY_CLOCK_HPP_

#include "time_engine.hpp"

NEY_NS_BEGIN

//! Class used to time. Contrary to the `timer` class, there is only one clock in the entire application

class clock
{
    public:

        //! Always call `get()` function to obtain the `clock` instance

        static clock& get()
        {
            static clock instance;

            return instance;
        }

        ~clock(){};

        //! Start timing

        clock& start();

        //! End timing

        clock& end();

        //! Set precision for printing

        clock& precision(unsigned p);
        
        //! Print clock value

        clock& print();

        //! Return time between `start()` and `end()` calls (in seconds)

        double time() const;

    private:
        time_engine engine_;
        unsigned decimal_places_;

        clock() : decimal_places_(DEFAULT_DECIMAL_PLACES){};
        clock(clock const&);
        void operator=(clock const&);
};

#include "detail/clock.cpp"

NEY_NS_END

#endif
