#ifndef NEY_MAIN_HPP_
#define NEY_MAIN_HPP_

#include <cstdlib>  // malloc(), realloc(), free(), size_t
#include <cstring>  // memset(), memcpy(), memmove(), memcmp()
#include <omp.h>

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

#define USE_ALIGNMENT TRUE

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

class config_t
{
    public:
        config_t()
        {
            #pragma omp parallel
            #pragma omp master

            threads = max_threads_ = omp_get_num_threads();
            #pragma omp barrier

            target = Intel;
            use_offloading = true;
        }

        unsigned max_threads() const
        {
            return max_threads_;
        }

        unsigned threads;
        target_enum target;
        bool use_offloading;

    private:
        unsigned max_threads_;
};
config_t config;
// namespace config

    //
    // enum target_enum
    // {
    //     Intel,
    //     GPU
    // };
    //
    // // Intel Xeon/Xeon Phi is the default architecture
    // target_enum target = Intel;
    //
    // // If target architecture == Intel, then setting this to true
    // // means that offloading to MIC can be used.
    // bool use_offloading = true;
    //


NEY_NS_END

#endif
