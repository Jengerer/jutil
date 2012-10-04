#ifndef WIDE_STRING_HPP
#define WIDE_STRING_HPP

#include "string/base_dynamic_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a wide character string representation.
     * Assumes string is writable; frees memory on destruction.
     */
    class __declspec(dllexport) WideString : public BaseDynamicString<wchar_t>
    {

    public:

        WideString( void );
        WideString( wchar_t* string, size_t length );
        virtual ~WideString( void );

        // Buffer management.
        bool write( const wchar_t* format, ... );
        bool write( const wchar_t* format, va_list args );

    };

}

#endif // WIDE_STRING_HPP
