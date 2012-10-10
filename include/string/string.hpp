#ifndef STRING_HPP
#define STRING_HPP

#include "string/constant_string.hpp"
#include "string/constant_wide_string.hpp"
#include "string/dynamic_string.hpp"
#include "string/dynamic_wide_string.hpp"

namespace JUTIL
{

    // Type definitions for general string usage.
    typedef BaseString<char> String;
    typedef BaseString<wchar_t> WideString;

}

#endif // STRING_HPP