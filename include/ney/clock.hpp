#ifndef NEY_CLOCK_HPP_
#define NEY_CLOCK_HPP_

#include "time_engine.hpp"

NEY_NS_BEGIN

class clock
{
    public:
        static clock& get()
        {
            static clock instance;

            return instance;
        }

        ~clock(){};

        clock& start();
        clock& end();
        clock& precision(unsigned p);
        clock& print();

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
