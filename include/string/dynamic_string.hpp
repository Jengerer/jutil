#ifndef DYNAMIC_STRING_HPP
#define DYNAMIC_STRING_HPP

#include "string/base_dynamic_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a C-string representation.
     * Assumes string is writable; frees memory on destruction.
     */
    class __declspec(dllexport) DynamicString : public BaseDynamicString<char>
    {

    public:

        DynamicString( void );
        DynamicString( char* string, size_t length );
        virtual ~DynamicString( void );

        // Buffer management.
        bool write( const char* format, ... );
        bool write( const char* format, va_list args );
    
    };

}

#endif // DYNAMIC_STRING_HPP
