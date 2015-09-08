#ifndef NEY_TIME_ENGINE_HPP_
#define NEY_TIME_ENGINE_HPP_

NEY_NS_BEGIN

class time_engine
{
    public:
        time_engine() : total_time_(0)
        {
        };
        ~time_engine(){};

        void start()
        {
            #if CC_CUDA
                cudaEventCreate(&cuda_start);
                cudaEventCreate(&cuda_stop);
                cudaEventRecord(cuda_start);
            #else
                 if (ney::config.target == Intel)
                    #if USE_OPENMP_TIME
                        start_time_ = omp_get_wtime();
                    #else
                        gettimeofday(&start, NULL);
                    #endif
            #endif
        };
        void end()
        {
            #if CC_CUDA
                cudaEventRecord(cuda_stop);
                cudaEventSynchronize(cuda_stop);
                float tmp = 0;
                cudaEventElapsedTime(&tmp, cuda_start, cuda_stop);
                total_time_ = tmp;
            #else
                if (ney::config.target == Intel)
                    #if USE_OPENMP_TIME
                        total_time_ = omp_get_wtime() - start_time_;
                    #else
                        gettimeofday(&end, NULL);
                        secs_used = (end.tv_sec - start.tv_sec);
                        total_time_ = secs_used + (end.tv_usec - start.tv_usec) / 1000000.0;
                    #endif
            #endif
        };

        double time() const
        {
            return total_time_;
        };

    private:
        double total_time_;

        #if CC_CUDA
            cudaEvent_t cuda_start, cuda_stop;
        #endif

        #if USE_OPENMP_TIME
            double start_time_;
        #else
            struct timeval start, end;
            double secs_used;
        #endif
};

NEY_NS_END

#endif
