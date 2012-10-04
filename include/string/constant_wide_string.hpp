#ifndef CONSTANT_WIDE_STRING_HPP
#define CONSTANT_WIDE_STRING_HPP

#include "string/base_constant_string.hpp"

namespace JUTIL
{

    /*
     * Constant string representation for wide character array.
     */
    class __declspec(dllexport) ConstantWideString : public BaseConstantString<wchar_t>
    {

    public:

        // Constructors from C-style string types.
        ConstantWideString( void );
        ConstantWideString( const wchar_t* string );
        ConstantWideString( const wchar_t* string, size_t length );
        ConstantWideString( const BaseString<wchar_t>& string );
        virtual ~ConstantWideString( void );

        // Additional string handling.
        void set_string( const wchar_t* string );

    };

}

#endif // CONSTANT_WIDE_STRING_HPP