#ifndef NEY_MAIN_HPP_
#define NEY_MAIN_HPP_

#include <cstdlib>  // malloc(), realloc(), free(), size_t
#include <cstring>  // memset(), memcpy(), memmove(), memcmp()
#include <omp.h>
#include <iomanip>
#include <unistd.h>
#include <iostream>
#include <cmath>

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

// Detect compiler

#if defined(__clang__)
    #define CC_CLANG TRUE
    #define CC_NAME "clang"
#elif defined(__ICC) || defined(__INTEL_COMPILER)
    #define CC_INTEL TRUE
    #define CC_NAME "intel"
#elif defined(__GNUC__) || defined(__GNUG__)
    #define CC_GNU TRUE
    #define CC_NAME "gnu"
#elif defined(__HP_cc) || defined(__HP_aCC)
    #define CC_HP TRUE
    #define CC_NAME "hp"
#elif defined(__IBMC__) || defined(__IBMCPP__)
    #define CC_IBM TRUE
    #define CC_NAME "ibm"
#elif defined(_MSC_VER)
    #define CC_MS TRUE
    #define CC_NAME "ms"
#elif defined(__PGI)
    #define CC_PORTLAND TRUE
    #define CC_NAME "portland"
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
    #define CC_ORACLE TRUE
    #define CC_NAME "oracle"
#endif

#ifdef __MIC__
#define MIC 1
#define VEC_LEN 64
#else
#define MIC 0
#define VEC_LEN 64
#endif

// Options

#define USE_ALIGNMENT TRUE
#define USE_MKL FALSE
#define USE_MIC FALSE
#define USE_OPENMP_TIME TRUE
#define DEFAULT_DECIMAL_PLACES 2

// -- Options

#if USE_ALIGNMENT && CC_INTEL
    #define ALIGNMENT_OK TRUE
#else
    #define ALIGNMENT_OK FALSE
#endif

#if ALIGNMENT_OK
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

#if USE_MKL
#include <mkl.h>
#endif

/****************
    Macros
****************/
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

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

namespace operation
{
    enum operation_t
    {   
        none,
        add, // addition
        mul  // multiplication
    };
}

namespace function
{
    enum function_t
    {
        none,
        sine,
        cosine
    };
}

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
        , compiler_(CC_NAME)
        {
            #pragma omp parallel
            #pragma omp master

            threads = max_threads_ = omp_get_num_threads();

            #pragma omp barrier

            #if USE_MIC
                #if MIC
                    running_on_mic = true;
                #else
                    #if USE_MKL
                        mic_count_ = mkl_mic_get_device_count();
                    #else
                        mic_count_ = _Offload_number_of_devices();
                    #endif
                #endif
            #endif

            srand(time(NULL));
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

        std::string compiler() const
        {
            return compiler_;
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
            std::cout << std::setw(x) << "Compiler: "   << std::setw(w) << compiler_ << std::endl;

            std::cout << std::endl;
        }

        unsigned threads;
        target_enum target;
        bool use_offloading;

    private:
        unsigned max_threads_;
        unsigned mic_count_;
        bool running_on_mic_;
        std::string compiler_;

};

config_t config;


NEY_NS_END

#endif
