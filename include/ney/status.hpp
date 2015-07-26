#ifndef NEY_STATUS_HPP_
#define NEY_STATUS_HPP_

NEY_NS_BEGIN

class status
{
    public:
        template <typename T> status(const operation<T>& obj);

        // [ms]
        double time() const;

    private:

        double total_time_;

        #if USE_OPENMP_TIME
            double start_time_;
        #else
            struct timeval start, end;
            double secs_used;
        #endif

};

#include "detail/status.inl"

NEY_NS_END

#endif
