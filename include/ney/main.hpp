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

// Reset compilers

#define CC_CLANG FALSE
#define CC_INTEL FALSE
#define CC_GNU FALSE
#define CC_HP FALSE
#define CC_IBM FALSE
#define CC_MS FALSE
#define CC_PORTLAND FALSE
#define CC_ORACLE FALSE
#define CC_CUDA FALSE

// Detect compiler

#if defined(__clang__)
    #undef CC_CLANG
    #define CC_CLANG TRUE
    #define CC_NAME "clang"
#elif defined(__CUDACC__)
    #undef CC_CUDA
    #define CC_CUDA TRUE
    #define CC_NAME "cuda"
#elif defined(__ICC) || defined(__INTEL_COMPILER)
    #undef CC_INTEL
    #define CC_INTEL TRUE
    #define CC_NAME "intel"
#elif defined(__GNUC__) || defined(__GNUG__)
    #undef CC_GNU
    #define CC_GNU TRUE
    #define CC_NAME "gnu"
#elif defined(__HP_cc) || defined(__HP_aCC)
    #undef CC_HP
    #define CC_HP TRUE
    #define CC_NAME "hp"
#elif defined(__IBMC__) || defined(__IBMCPP__)
    #undef CC_IBM
    #define CC_IBM TRUE
    #define CC_NAME "ibm"
#elif defined(_MSC_VER)
    #undef CC_MS
    #define CC_MS TRUE
    #define CC_NAME "ms"
#elif defined(__PGI)
    #undef CC_PORTLAND
    #define CC_PORTLAND TRUE
    #define CC_NAME "portland"
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
    #undef CC_ORACLE
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

//! Options
//! That part can be changed by anyone using library

#define USE_ALIGNMENT TRUE
#define USE_MKL FALSE
// #define USE_MIC TRUE
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

#ifndef USE_MIC
    #if CC_GNU
        #define USE_MIC TRUE
    #elif CC_INTEL
        #define USE_MIC TRUE
    #endif
#endif


/****************
    Macros
****************/
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define OFFLOAD_OK (ney::config.mic_count() > 0 && ! ney::config.running_on_mic())
#define OFFLOAD_FORCE (this->force_offloading_ && CC_GNU == TRUE)

NEY_NS_BEGIN

//! Available targets. `Intel` covers Intel Xeon/Xeon Phi/desktop processors; `GPU` covers CUDA GPU cards

enum target_enum
{
    Intel,
    GPU
};

//! Names of the available targets. Must be compatible with `enum target_enum`

static const std::string target_array[] =
{
    "Intel",
    "GPU",
};

template <typename T>
class value
{

public:
    value(T v)
    {
        val = v;
    }
    T val;

};

//! List of available `condition`s. They can be added to functions (eg. swap) to control the behaviour

namespace condition
{
    //! Returns true if a is greater than b

    template <typename T>
    inline bool gt(const T* a, const T* b)
    {
        if (*a > *b)
            return true;
        else
            return false;
    }

    //! Returns true if a is less than b

    template <typename T>
    inline bool lt(const T* a, const T* b)
    {
        if (*a < *b)
            return true;
        else
            return false;
    }

    //! Returns true if the argument is a letter

    template <typename T>
    inline bool letter(const T* a)
    {
        if ((*a >= 'a' && *a <= 'z') || (*a >= 'A' && *a <= 'Z'))
            return true;
        else
            return false;
    }

    //! Returns true if the first argument is a letter and second is not

    template <typename T>
    inline bool letter_space(const T* a, const T* b)
    {
        if (letter(a) && ! letter(b))
            return true;
        else
            return false;
    }
}

//! List of available `operation`s. Each operation is executed on two operands

namespace operation
{
    enum operation_t
    {
        none = 1,
        add = 2, // addition
        mul = 3  // multiplication
    };
}

//! List of available `function`s. Each function is executed on a single argument

namespace function
{
    enum function_t
    {
        none = 100,
        sine = 101,
        cosine = 102,

        // changes chars to lowercase

        lower = 103,

        // changes chars to uppercase

        upper = 104
    };
}

//! Config class. An instance of the config class is created automatically

class config_t
{
    public:

        //! Constructor, sets default parameters

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
            #define NUM_THREADS ney::config.threads

            #pragma omp barrier

            #if MIC
                this->running_on_mic_ = true;
            #endif
                    // #if USE_MKL
                        // this->mic_count_ = mkl_mic_get_device_count();
                    // #else

            #if USE_MIC && ! CC_GNU
                this->mic_count_ = _Offload_number_of_devices();
            #endif

            srand(time(NULL));
        }

        //! Returns maximum number of threads available in the system

        unsigned max_threads() const
        {
            return max_threads_;
        }

        //! Returns number of MICs available in the system

        unsigned mic_count() const
        {
            return mic_count_;
        }

        //! Returns `true` if the program is being run natively on Intel Xeon Phi, `false` otherwise`

        bool running_on_mic() const
        {
            return running_on_mic_;
        }

        //! Returns name of the compiler the program has been compiled with

        std::string compiler() const
        {
            return compiler_;
        }

        //! Prints configuration parameters

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

        //! Number of threads that should be used

        unsigned threads;

        //! Target architecture. Available are: Intel (covers Intel Xeon/Xeon/Phi/desktop processors) and GPU (covers CUDA GPU cards)

        target_enum target;

        //! Set to `true` if program can use offloading (default is `true`)

        bool use_offloading;

    private:
        unsigned max_threads_;
        unsigned mic_count_;
        bool running_on_mic_;
        std::string compiler_;
};

//! Configuration object used by the library

config_t config;


NEY_NS_END

#endif
