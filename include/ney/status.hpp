#ifndef NEY_STATUS_HPP_
#define NEY_STATUS_HPP_

NEY_NS_BEGIN

class status
{
    public:
        // template <typename T> status(const operation<T>& obj);
        template <typename T> status(const random<T>& obj);

        // [ms]
        double time() const;
        bool success() const;
        std::string error() const;

    private:

        double total_time_;
        bool success_;
        std::string error_msg_;

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
