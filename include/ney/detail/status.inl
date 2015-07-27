#include "../main.hpp"
#include "../status.hpp"
#include "../random.hpp"

#if ! USE_OPENMP_TIME
    #include <sys/time.h>
#endif

#define START_TIMING if (obj.time_) start_timing();
#define END_TIMING if (obj.time_) end_timing();

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
    init();

    // Validate

    if (obj.min_ >= obj.max_)
    {
        success_ = false;
        error_msg_ = "Min value must be smaller than max value.";

        return;
    }

    // Run

    START_TIMING
    obj.run();
    END_TIMING
}

template <typename T>
status::status(const fill<T>& obj)
{
    init();

    // Run

    START_TIMING
    obj.run();
    END_TIMING
}

// template <typename T>
// status::status(const operation<T>& obj)
// {
//     std::cout << "Hej operation" << std::endl;
//     std::cout << "time: " << obj.time_ << std::endl;
//     // std::cout << "TIME: " << obj.time_ << std::endl;
//
//     if (obj.time_)
//         if (ney::config.target == Intel)
//             #if USE_OPENMP_TIME
//                 start_time_ = omp_get_wtime();
//             #else
//                 gettimeofday(&start, NULL);
//             #endif
//
//     obj.run();
//
//     if (obj.time_)
//         if (ney::config.target == Intel)
//             #if USE_OPENMP_TIME
//                 total_time_ = omp_get_wtime() - start_time_;
//             #else
//                 gettimeofday(&end, NULL);
//                 secs_used = (end.tv_sec - start.tv_sec);
//                 total_time_ = secs_used + (end.tv_usec - start.tv_usec) / 1000000.0;
//             #endif
// }

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
