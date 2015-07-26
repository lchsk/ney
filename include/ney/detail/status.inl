#include "../status.hpp"
// #include <iostream>
#if ! USE_OPENMP_TIME
    #include <sys/time.h>
#endif

template <typename T>
// inline
status::status(const operation<T>& obj)
{
    std::cout << "SHOULD TIME: " << obj.time_ << std::endl;

    if (obj.time_)
        if (ney::config.target == Intel)
            #if USE_OPENMP_TIME
                start_time_ = omp_get_wtime();
            #else
                gettimeofday(&start, NULL);
            #endif

    obj.run();

    if (obj.time_)
        if (ney::config.target == Intel)
            #if USE_OPENMP_TIME
                total_time_ = omp_get_wtime() - start_time_;
            #else
                gettimeofday(&end, NULL);
                secs_used = (end.tv_sec - start.tv_sec);
                total_time_ = secs_used + (end.tv_usec - start.tv_usec) / 1000000.0;
            #endif
}

double status::time() const
{
    return total_time_;
}
