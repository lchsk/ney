#ifndef NEY_STATUS_HPP_
#define NEY_STATUS_HPP_

NEY_NS_BEGIN

//! Status class
/*!
    Checks if parameters are valid and invokes functions. Informs whether a function resulted in an error
*/
class status
{
    public:
        
        //! Constructor invoked when status created like this: `ney::status s;`
        
        status();

        //! Invokes `ney::random()`
        
        template <typename T> status(const random<T>& obj);

        //! Invokes `ney::fill()`

        template <typename T> status(const fill<T>& obj);
        
        //! Invokes `ney::replace()`

        template <typename T> status(const replace<T>& obj);
        
        //! Invokes `ney::count()`

        template <typename T> status(const count<T>& obj);
        
        //! Invokes `ney::compare()`

        template <typename T> status(const compare<T>& obj);
        
        //! Invokes `ney::reduce()`

        template <typename T> status(const reduce<T>& obj);
        
        //! Invokes `ney::apply()`

        template <typename T> status(const apply<T>& obj);

        //! Returns how long a function took to finish (in seconds). To work correctly, first `time()` needs to be called on the function itself

        double time() const;

        //! Returns `true` if function parameters are valid, `false` otherwise

        bool success() const;

        //! If `success()` if `false`, then `error()` gives an error message. Should be empty otherwise

        std::string error() const;

        //! Prints a status, eg. `status_.print();`

        status& print();

        //! Prints a status using `std::cout`, eg., `std::cout << status_ << std::endl;`
        friend std::ostream& operator<<(std::ostream& s, const status& v);

    private:

        void init();
        time_engine engine_;

        bool success_;
        std::string error_msg_;
};

#include "detail/status.cpp"

NEY_NS_END

#endif
