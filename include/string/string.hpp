#ifndef STRING_HPP
#define STRING_HPP

#include "string/base_dynamic_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a C-string representation.
     * Assumes string is writable; frees memory on destruction.
     */
    class __declspec(dllexport) String : public BaseDynamicString<char>
    {

    public:

        String( void );
        String( char* string, size_t length );
        virtual ~String( void );

        // Buffer management.
        bool write( const char* format, ... );
        bool write( const char* format, va_list args );
    
    };

}

#endif // STRING_HPP
