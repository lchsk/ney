#include "../main.hpp"
#include "../status.hpp"
#include "../random.hpp"
#include "../replace.hpp"

#if ! USE_OPENMP_TIME
    #include <sys/time.h>
#endif

#define START_TIMING if (obj.time_) start_timing();
#define END_TIMING if (obj.time_) end_timing();
#define RUN_FUNCTION START_TIMING \
                        obj.run(); \
                        END_TIMING
#define INIT_FUNCTION init();

void status::start_timing()
{
    if (ney::config.target == Intel)
        #if USE_OPENMP_TIME
            start_time_ = omp_get_wtime();
        #else
            gettimeofday(&start, NULL);
        #endif
}

void status::end_timing()
{
    if (ney::config.target == Intel)
        #if USE_OPENMP_TIME
            total_time_ = omp_get_wtime() - start_time_;
        #else
            gettimeofday(&end, NULL);
            secs_used = (end.tv_sec - start.tv_sec);
            total_time_ = secs_used + (end.tv_usec - start.tv_usec) / 1000000.0;
        #endif
}

void status::init()
{
    total_time_ = 0.0;
    success_ = true;
    error_msg_ = "";
}

template <typename T>
status::status(const random<T>& obj)
{
    INIT_FUNCTION

    if (obj.min_ >= obj.max_)
    {
        success_ = false;
        error_msg_ = "Min value must be smaller than max value.";

        return;
    }

    RUN_FUNCTION
}

template <typename T>
status::status(const fill<T>& obj)
{
    INIT_FUNCTION

    RUN_FUNCTION
}

template <typename T>
status::status(const replace<T>& obj)
{
    INIT_FUNCTION

    RUN_FUNCTION
}

template <typename T>
status::status(const count<T>& obj)
{
    INIT_FUNCTION

    RUN_FUNCTION
}

double inline status::time() const
{
    return total_time_;
}

bool inline status::success() const
{
    return success_;
}

std::string inline status::error() const
{
    return error_msg_;
}
