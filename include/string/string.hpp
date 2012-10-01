#ifndef STRING_HPP
#define STRING_HPP

#include "string/string_builder.hpp"
#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a C-string representation.
     * Assumes string is writable; frees memory on destruction.
     */
    class __declspec(dllexport) String : public BaseString<char>
    {

    public:

        String( StringBuilder* string_builder );
        String( char* string, size_t length );
        virtual ~String( void );

        // Attribute functions.
        char* get_string( void );
        virtual const char* get_string( void ) const;

    private:

        char* string_;
    
    };

}

#endif // STRING_HPP
