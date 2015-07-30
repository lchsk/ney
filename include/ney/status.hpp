#ifndef NEY_STATUS_HPP_
#define NEY_STATUS_HPP_

NEY_NS_BEGIN

class status
{
    public:
        template <typename T> status(const random<T>& obj);
        template <typename T> status(const fill<T>& obj);
        template <typename T> status(const replace<T>& obj);
        template <typename T> status(const count<T>& obj);
        template <typename T> status(const compare<T>& obj);

        // [ms]
        double time() const;
        bool success() const;
        std::string error() const;

    private:

        void init();

        double total_time_;
        bool success_;
        std::string error_msg_;

        void start_timing();
        void end_timing();

        #if USE_OPENMP_TIME
            double start_time_;
        #else
            struct timeval start, end;
            double secs_used;
        #endif
};

#include "detail/status.cpp"

NEY_NS_END

#endif
