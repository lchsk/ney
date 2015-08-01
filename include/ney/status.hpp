#ifndef NEY_STATUS_HPP_
#define NEY_STATUS_HPP_

NEY_NS_BEGIN

class status
{
    public:
        status(){};
        template <typename T> status(const random<T>& obj);
        template <typename T> status(const fill<T>& obj);
        template <typename T> status(const replace<T>& obj);
        template <typename T> status(const count<T>& obj);
        template <typename T> status(const compare<T>& obj);
        template <typename T> status(const reduce<T>& obj);
        template <typename T> status(const apply<T>& obj);

        // [ms]
        double time() const;
        bool success() const;
        std::string error() const;

        status& print();

        // template <typename T2>
        friend std::ostream& operator<<(std::ostream& s, const status& v);

    private:

        void init();
        time_engine engine_;

        // double total_time_;
        bool success_;
        std::string error_msg_;

        // void start_timing();
        // void end_timing();

        // #if USE_OPENMP_TIME
        //     double start_time_;
        // #else
        //     struct timeval start, end;
        //     double secs_used;
        // #endif
};

#include "detail/status.cpp"

NEY_NS_END

#endif
