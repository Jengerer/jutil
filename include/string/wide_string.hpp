#ifndef STRING_HPP
#define STRING_HPP

#include "string/wide_string_builder.hpp"
#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a wide string representation.
     * Assumes string is writable; frees memory on destruction.
     */
    class __declspec(dllexport) WideString : public BaseString<wchar_t>
    {

    public:

        WideString( WideStringBuilder* string_builder );
        WideString( wchar_t* string, size_t length );
        virtual ~WideString( void );

        // Attribute functions.
        wchar_t* get_string( void );
        virtual const wchar_t* get_string( void ) const;

    private:

        wchar_t* string_;
    
    };

}

#endif // STRING_HPP
