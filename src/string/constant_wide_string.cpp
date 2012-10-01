#include "string/constant_wide_string.hpp"
#include <string.h>

namespace JUTIL
{

    /*
     * Constant string default constructor.
     */
    ConstantWideString::ConstantWideString( void )
    {
        string_ = nullptr;
        set_length( 0 );
    }

    /*
     * Constant string constructor from null-terminated string.
     */
    ConstantWideString::ConstantWideString( const wchar_t* string )
    {
        set_string( string );
    }

    /*
     * Constant string constructor from string with length.
     */
    ConstantWideString::ConstantWideString( const wchar_t* string, unsigned int length )
    {
        set_string( string, length );
    }

    /*
     * Constant string constructor from managed string.
     * Assumes managed string will out-live constant string usage.
     */
    ConstantWideString::ConstantWideString( const BaseString<wchar_t>& string )
    {
        set_string( &string );
    }

    /*
     * Constant string destructor.
     */
    ConstantWideString::~ConstantWideString( void )
    {
        // We're not managing string, so don't delete.
    }

    /*
     * Get constant string pointer.
     */
    const wchar_t* ConstantWideString::get_string( void ) const
    {
        return string_;
    }

    /*
     * String handle updating by base string.
     */
    void ConstantWideString::set_string( const BaseString<wchar_t>* other )
    {
        string_ = other->get_string();
        set_length( other->get_length() );
    }

    /*
     * String handle updating by null-terminated string.
     */
    void ConstantWideString::set_string( const wchar_t* string )
    {
        unsigned int length = wcslen( string );
        set_string( string, length );
    }

    /*
     * String handle updating by string and length.
     */
    void ConstantWideString::set_string( const wchar_t* string, unsigned int length )
    {
        string_ = string;
        set_length( length );
    }

}
