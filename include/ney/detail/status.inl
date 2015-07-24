#include "../status.hpp"
#include <iostream>

template <typename T>
inline
status::status(const fill<T>& obj)
{
    obj.run();
}
