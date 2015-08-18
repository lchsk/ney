#include "../main.hpp"
#include "../status.hpp"
#include "../random.hpp"
#include "../replace.hpp"

#if ! USE_OPENMP_TIME
    #include <sys/time.h>
#endif

#define START_TIMING if (obj.time_) engine_.start();
#define END_TIMING if (obj.time_) engine_.end();
#define RUN_FUNCTION START_TIMING \
                        obj.run(); \
                        END_TIMING
#define INIT_FUNCTION init();

void status::init()
{
    success_ = false;
    error_msg_ = "";
}

status::status()
{
    INIT_FUNCTION
}

template <typename T>
status::status(const random<T>& obj)
{
    INIT_FUNCTION

    if (obj.min_ >= obj.max_)
    {
        error_msg_ = "min value must be smaller than max value";

        return;
    }

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const fill<T>& obj)
{
    INIT_FUNCTION

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const replace<T>& obj)
{
    INIT_FUNCTION

    if (obj.v_ == NULL)
    {
        error_msg_ = "use in() to specify a vector";

        return;
    }

    // TODO: validate new_
    // if (obj.new_ == NULL)
    // {
    //     success_ = false;
    //     error_msg_ = "use with() to specify a new value";

    //     return;
    // }

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const count<T>& obj)
{
    INIT_FUNCTION

    if (obj.count_ == NULL)
    {
        error_msg_ = "use output() to specify an output variable";

        return;
    }

    if (obj.v_ == NULL)
    {
        error_msg_ = "use in() to specify a vector";

        return;
    }

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const swap<T>& obj)
{
    INIT_FUNCTION

    if (obj.v1_ == NULL)
    {
        error_msg_ = "use vector1() to specify first input vector";

        return;
    }

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const unique<T>& obj)
{
    INIT_FUNCTION

    // currently no output vector can be specified
    // if (obj.out_ == NULL)
    // {
    //     error_msg_ = "use output() to specify the output vector";
    //
    //     return;
    // }

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const sort<T>& obj)
{
    INIT_FUNCTION

    success_ = true;

    RUN_FUNCTION
}


template <typename T>
status::status(const compare<T>& obj)
{
    INIT_FUNCTION

    if (obj.output_ == NULL)
    {
        error_msg_ = "use output() to specify an output boolean vector";

        return;
    }

    if (obj.v1_ == NULL)
    {
        error_msg_ = "use vector1() to specify first input vector";

        return;
    }

    if (obj.v2_ == NULL)
    {
        error_msg_ = "use vector2() to specify second input vector";

        return;
    }

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const reduce<T>& obj)
{
    INIT_FUNCTION

    if (obj.output_ == NULL)
    {
        error_msg_ = "use output() to specify an output variable";

        return;
    }

    if (obj.operation_ == operation::none)
    {
        error_msg_ = "use use() to specify an operation";

        return;
    }

    success_ = true;

    RUN_FUNCTION
}

template <typename T>
status::status(const apply<T>& obj)
{
    INIT_FUNCTION

    // Use cases:
    // (1) apply(fun).vector1(vec1); -> output in vec1
    // (2) apply(op).vector1(vec1).vector2(vec2); -> output in vec1
    // (3) apply(op).vector1(vec1).vector2(vec2).value(scalar); -> output in vec1
    // (4) apply(op).vector1(vec1).value(scalar); -> output in vec1

    if (obj.f_ != function::none && obj.v1_ != NULL)
    {
        // use case 1

        success_ = true;
    }
    else if (obj.op_ != operation::none && obj.v1_ != NULL)
    {
        if (obj.v2_ != NULL)
        {
            // use case 2 or 3

            success_ = true;
        }
        else if (obj.use_scalar_)
        {
            // use case 4
            success_ = true;
        }
        else
        {
            success_ = false;
            error_msg_ = "use value() to specify scalar value";
        }
    }
    else
    {
        // Validation error - function will not be executed
        // Prepare an error message

        if (obj.v1_ == NULL)
            error_msg_ = "use vector1() to specify first input vector";

        return;
    }

    RUN_FUNCTION
}

double inline status::time() const
{
    return engine_.time();
}

bool inline status::success() const
{
    return success_;
}

std::string inline status::error() const
{
    return error_msg_;
}

status& status::print()
{
    if ( this->success_)
    {
        std::cout << "status(success, total time: "
            << std::setiosflags(std::ios::fixed)
            << std::setprecision(2)
            << this->engine_.time()
            << ")";
    }
    else
    {
        std::cout << "status(error: " << this->error_msg_ << ")";
    }

    return *this;
}

std::ostream& operator<<(std::ostream& s, status& v)
{
    v.print();

    return s;
}
