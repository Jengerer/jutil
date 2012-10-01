#include "string/constant_string.hpp"
#include <string.h>

namespace JUTIL
{

    /*
     * Constant string default constructor.
     */
    ConstantString::ConstantString( void )
    {
        string_ = nullptr;
        set_length( 0 );
    }

    /*
     * Constant string constructor from null-terminated string.
     */
    ConstantString::ConstantString( const char* string )
    {
        set_string( string );
    }

    /*
     * Constant string constructor from string with length.
     */
    ConstantString::ConstantString( const char* string, unsigned int length )
    {
        set_string( string, length );
    }

    /*
     * Constant string constructor from managed string.
     * Assumes managed string will out-live constant string usage.
     */
    ConstantString::ConstantString( const BaseString<char>& string )
    {
        set_string( &string );
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

    /*
     * String handle updating by base string.
     */
    void ConstantString::set_string( const BaseString<char>* other )
    {
        string_ = other->get_string();
        set_length( other->get_length() );
    }

    /*
     * String handle updating by null-terminated string.
     */
    void ConstantString::set_string( const char* string )
    {
        unsigned int length = strlen( string );
        set_string( string, length );
    }

    /*
     * String handle updating by string and length.
     */
    void ConstantString::set_string( const char* string, unsigned int length )
    {
        string_ = string;
        set_length( length );
    }

}
