#include "main.hpp"
#include "vector.hpp"

#ifndef NEY_BASE_OPERATION_HPP_
#define NEY_BASE_OPERATION_HPP_

NEY_NS_BEGIN

class status;

//! This is a base class for all operations (eg. fill, reduce etc.)

template <class T, template <typename> class Derived>
class base_operation
{
    public:

        //! Default constructor

        base_operation();

        virtual ~base_operation(){};

        //! Use `time()` if you want to measure execution time of a funtion

        virtual Derived<T>& time();

        //! Change precision of the clock used to measure execution time

        virtual Derived<T>& precision(T precision);

        //! Add a condition (function that returns true/false); works on some operations

        virtual Derived<T>& condition(bool (*cond)(const T*, const T*));

        //! Force offloading (regardless of data size)

        virtual Derived<T>& force_offloading();

        //! Must be overriden

        virtual void run() const = 0;

    protected:
        void detect_data_type();
        bool is_integer_;
        bool force_offloading_;
        mutable bool offloaded_;
        T precision_;
        bool (*cond_)(const T*, const T*);

        // work sharing (between host and MIC)

        void set_worksharing(const vector<T>* v) const;
        mutable int from1, from2;
        mutable int to1, to2;

    private:
        friend class status;
        bool time_;
};

#include "detail/base_operation.cpp"

NEY_NS_END

#endif
