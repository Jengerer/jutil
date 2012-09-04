#ifndef STRING_HPP
#define STRING_HPP

#include "string_builder.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a C-string representation.
     * Assumes string is writable; frees memory on destruction.
     */
    class __declspec(dllexport) String
    {

    public:

        String( StringBuilder* string_builder );
        String( char* str, size_t length );
        ~String( void );

        // Attribute functions.
        const char* get_string( void ) const;
        size_t get_length( void ) const;

    private:

        char* str_;
        size_t length_;
    
    };

}

#endif // STRING_HPP
