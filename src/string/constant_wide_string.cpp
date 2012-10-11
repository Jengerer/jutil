#include "string/constant_wide_string.hpp"
#include <string.h>

namespace JUTIL
{

    /*
     * Constant string default constructor.
     */
    ConstantWideString::ConstantWideString( void )
    {
        // Nothing special.
    }

    /*
     * Constant string constructor from null-terminated string.
     */
    ConstantWideString::ConstantWideString( const wchar_t* string )
    {
		size_t length = wcslen( string );
        set_string( string, length );
    }

    /*
     * Constant string constructor from string with length.
     */
    ConstantWideString::ConstantWideString( const wchar_t* string, unsigned int length )
        : BaseConstantString<wchar_t>( string, length )
    {
        // Nothing special.
    }

    /*
     * Constant string constructor from managed string.
     * Assumes managed string will out-live constant string usage.
     */
    ConstantWideString::ConstantWideString( const BaseString<wchar_t>* string )
        : BaseConstantString<wchar_t>( string )
    {
        // Nothing special.
    }

    /*
     * Constant string destructor.
     */
    ConstantWideString::~ConstantWideString( void )
    {
        // We're not managing string, so don't delete.
    }

}
