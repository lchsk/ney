#ifndef NEY_MAIN_HPP_
#define NEY_MAIN_HPP_

#include <cstdlib>  // malloc(), realloc(), free(), size_t
#include <cstring>  // memset(), memcpy(), memmove(), memcmp()
#include <omp.h>
#include <iomanip>
#include <unistd.h>


#ifndef LIB_NAME
#define LIB_NAME ney
#endif

#ifndef NEY_NS_BEGIN
#define NEY_NS_BEGIN namespace LIB_NAME {
#endif
#ifndef NEY_NS_END
#define NEY_NS_END }
#endif

#define NEY_TO_STRING(x) NEY_DO_STRING(x)
#define NEY_DO_STRING(x) #x

#define NEY_MAJOR_VERSION 0
#define NEY_MINOR_VERSION 1
#define NEY_PATCH_VERSION 0
#define NEY_VERSION_STRING \
    NEY_TO_STRING(NEY_MAJOR_VERSION.NEY_MINOR_VERSION.NEY_PATCH_VERSION)

#define TRUE 1
#define FALSE 0

#ifdef __MIC__
#define MIC 1
#define VEC_LEN 64
#else
#define MIC 0
#define VEC_LEN 64
#endif

// Options

#define USE_ALIGNMENT TRUE
#define USE_MKL TRUE
#define USE_OPENMP_TIME TRUE

// -- Options

#if USE_ALIGNMENT
#define MALLOC _mm_malloc
#define FREE _mm_free
#define ALIGN VEC_LEN
#define ALIGN_CODE __attribute__((aligned(ALIGN)))
#else
#define MALLOC malloc
#define FREE free
#define ALIGN
#define ALIGN_CODE
#endif

#if USE_MKL == TRUE
#include <mkl.h>
#endif



/****************
    Macros
****************/
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

// namespace ney
// {
//     using std::size_t;
// }

/****************
    Configuration
    -------------
    Currently configuration consists of two variables:
        - target = { Intel, GPU } which sets architecture on which
        the program will be running on
        - use_offloading = { true, false }
****************/


NEY_NS_BEGIN

enum target_enum
{
    Intel,
    GPU
};

static const std::string target_array[] =
{
    "Intel",
    "GPU",
};

class config_t
{
    public:
        config_t()
        : target(Intel)
        , use_offloading(true)
        , running_on_mic_(false)
        , mic_count_(0)
        , threads(1)
        , max_threads_(1)
        {
            #pragma omp parallel
            #pragma omp master

            threads = max_threads_ = omp_get_num_threads();

            #pragma omp barrier

            #if MIC == 1
                running_on_mic = true;
            #else
                #if USE_MKL == TRUE
                    mic_count_ = mkl_mic_get_device_count();
                #endif
            #endif
        }

        unsigned max_threads() const
        {
            return max_threads_;
        }

        unsigned mic_count() const
        {
            return mic_count_;
        }

        bool running_on_mic() const
        {
            return running_on_mic_;
        }

        void print() const
        {
            int w = 1;
            int x = 16;

            // char* tmp = getenv("USER");

            char hostname[128];
            if (gethostname(hostname, 128) == 0)
            {
                std::string host(hostname);
                std::cout << "Running on " << host << std::endl;
            }

            std::cout << std::setw(x) << "Architecture: "   << std::setw(w) << target_array[target] << std::endl;
            std::cout << std::setw(x) << "Threads used: "   << std::setw(w) << threads << std::endl;
            std::cout << std::setw(x) << "Max threads: "    << std::setw(w) << max_threads_ << std::endl;
            std::cout << std::setw(x) << "Number of MICs: " << std::setw(w) << mic_count_ << std::endl;
            std::cout << std::setw(x) << std::boolalpha     << std::setw(w) << "Use offloading: " << use_offloading << std::endl;
            std::cout << std::setw(x) << std::boolalpha     << std::setw(w) << "Running on MIC: " << running_on_mic_ << std::endl;

            std::cout << std::endl;
        }

        unsigned threads;
        target_enum target;
        bool use_offloading;

    private:
        unsigned max_threads_;
        unsigned mic_count_;
        bool running_on_mic_;

};
config_t config;

NEY_NS_END

#endif
