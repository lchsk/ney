#include "../main.hpp"
#include "../base_operation.hpp"

//! (1 / DEVICE) is executed on the device

#define DEVICE 5.0

template <class T, template <typename> class Derived>
inline
base_operation<T, Derived>::base_operation() : time_(false), is_integer_(true), cond_(NULL), force_offloading_(false), offloaded_(false)
{
    // #ifndef OFFLOADING
    // {
    //     // IF statement here must allow for testing with g++
    //
    //     // if (USE_MIC && CC_INTEL && ney::config.mic_count() > 0 && ! ney::config.running_on_mic() && ney::config.use_offloading)
    //     if (
    //         USE_MIC && ney::config.use_offloading &&
    //         ((
    //             CC_INTEL == FALSE &&
    //             ney::config.mic_count() > 0 &&
    //             ! ney::config.running_on_mic())
    //         )
    //         // || (CC_GNU == TRUE)
    //         )
    //     {
    //         #undef OFFLOADING
    //         #define OFFLOADING TRUE
    //     }
    //     else
    //     {
    //         #undef OFFLOADING
    //         #define OFFLOADING FALSE
    //     }
    // }
    // #endif
}

template <class T, template <typename> class Derived>
inline Derived<T>& base_operation<T, Derived>::time()
{
    time_ = true;

    return static_cast<Derived<T> &>(*this);
}

template <class T, template <typename> class Derived>
inline Derived<T>& base_operation<T, Derived>::force_offloading()
{
    force_offloading_ = true;

    return static_cast<Derived<T> &>(*this);
}

template <class T, template <typename> class Derived>
inline Derived<T>& base_operation<T, Derived>::precision(T precision)
{
    precision_ = precision;

    return static_cast<Derived<T> &>(*this);
}

template <class T, template <typename> class Derived>
inline void base_operation<T, Derived>::detect_data_type()
{
    if (2 == (T) 2.5)
        is_integer_ = true;
    else
    {
        is_integer_ = false;
        precision_ = 0.00001;
    }
}

template <class T, template <typename> class Derived>
inline void base_operation<T, Derived>::set_worksharing(const vector<T>* v) const
{
    // Part 1 is executed on the device

    from1 = v->from();
    to1 = floor(v->length() / DEVICE) * v->stride() + v->stride();

    // Number of elements executed on the device

    int elements = ceil((to1 - from1) / float(v->stride()));

    // Part 2 is executed on the host

    from2 = from1 + elements * v->stride();
    to2 = v->to();
}

template <class T, template <typename> class Derived>
inline Derived<T>& base_operation<T, Derived>::condition(bool (*cond)(const T*, const T*))
{
    cond_ = cond;

    return static_cast<Derived<T> &>(*this);
}
