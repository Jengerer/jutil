#include "string/constant_string.hpp"
#include <string.h>

namespace JUTIL
{

    /*
     * Constant string constructor from null-terminated string.
     */
    ConstantString::ConstantString( const char* string )
    {
        string_ = string;
        unsigned int length = strlen( string );
        set_length( length );
    }

    /*
     * Constant string constructor from managed string.
     * Assumes managed string will out-live constant string usage.
     */
    ConstantString::ConstantString( const String& string )
    {
        string_ = string.get_string();
        set_length( string.get_length() );
    }

    /*
     * Constant string constructor from string with length.
     */
    ConstantString::ConstantString( const char* string, unsigned int length )
    {
        string_ = string;
        set_length( length );
    }

    /*
     * Constant string destructor.
     */
    ConstantString::~ConstantString( void )
    {
        // We're not managing string, so don't delete.
    }

    /*
     * Get constant string pointer.
     */
    const char* ConstantString::get_string( void ) const
    {
        return string_;
    }

}
