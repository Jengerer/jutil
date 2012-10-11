#include "string/constant_string.hpp"
#include <string.h>

namespace JUTIL
{

    /*
     * Constant string default constructor.
     */
    ConstantString::ConstantString( void )
    {
    }

    /*
     * Constant string constructor from null-terminated string.
     */
    ConstantString::ConstantString( const char* string )
    {
		size_t length = strlen( string );
        set_string( string, length );
    }

    /*
     * Constant string constructor from string with length.
     */
    ConstantString::ConstantString( const char* string, unsigned int length )
        : BaseConstantString<char>( string, length )
    {
    }

    /*
     * Constant string constructor from managed string.
     * Assumes managed string will out-live constant string usage.
     */
    ConstantString::ConstantString( const BaseString<char>* string )
        : BaseConstantString<char>( string )
    {
    }

    /*
     * Constant string destructor.
     */
    ConstantString::~ConstantString( void )
    {
    }

}
