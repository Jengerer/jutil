#include "string/string.hpp"

/*
 * String constructor from null-terminated string.
 */
String::String( char* str )
{
    str_ = str;
    length_ = strlen( str_ );
}

/*
 * String constructor from string and length.
 * Does not assume string is null-terminated; does not terminate it itself.
 */
String::String( char* str, size_t length )
{
    str_ = str;
    length_ = length;
}

/*
 * String destructor.
 */
String::~String( void )
{
    // Does nothing...
}

/*
 * Get representation of C string.
 */
const char* get_string( void ) const
{
    return str_;
}

/*
 * Get length of the string.
 */
size_t get_length( void ) const
{
    return length_;
}
