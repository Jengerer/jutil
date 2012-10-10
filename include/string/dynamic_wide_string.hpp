#ifndef DYNAMIC_WIDE_STRING_HPP
#define DYNAMIC_WIDE_STRING_HPP

#include "string/base_dynamic_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a wide character string representation.
     * Assumes string is writable; frees memory on destruction.
     */
    class __declspec(dllexport) DynamicWideString : public BaseDynamicString<wchar_t>
    {

    public:

        DynamicWideString( void );
        DynamicWideString( wchar_t* string, size_t length );
        virtual ~DynamicWideString( void );

        // Buffer management.
        bool write( const wchar_t* format, ... );
        bool write( const wchar_t* format, va_list args );

    };

}

#endif // DYNAMIC_WIDE_STRING_HPP
