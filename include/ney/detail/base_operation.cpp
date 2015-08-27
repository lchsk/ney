#include "../main.hpp"
#include "../base_operation.hpp"

template <class T, template <typename> class Derived>
inline
base_operation<T, Derived>::base_operation() : time_(false), is_integer_(true), cond_(NULL), force_offloading_(false), offloaded_(false)
{}

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

    // 1 / DEVICE is executed on the device

    float DEVICE = 5.0;

    int len = v->length();
    int f = floor(len / DEVICE);

    from1 = v->from();
    to1 = f * v->stride() + v->stride();
    int el1 = ceil((to1 - from1) / float(v->stride()));
    // to1 = floor(v->to() / 3.0);

    // Part 2 is executed on the host

    // if (v->length() > to1)
    {
        // from2 = to1 - 1 + v->stride();
        // from2 = to1;
        from2 = from1 + el1 * v->stride();
        to2 = v->to();
    }
    // else
    // {
    //     from2 = to2 = 0;
    // }

    std::cout << "el: " << el1 << "\n";
    std::cout << "d: " << from1 << " -> " << to1 << " h: " << from2 << " -> " << to2 << "\n";
}

template <class T, template <typename> class Derived>
inline Derived<T>& base_operation<T, Derived>::condition(bool (*cond)(const T*, const T*))
{
    cond_ = cond;

    return static_cast<Derived<T> &>(*this);
}
