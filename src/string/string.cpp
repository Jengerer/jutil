#include "string/string.hpp"
#include <stdlib.h>
#include <string.h>

namespace JUTIL
{

    /*
     * String constructor from string builder.
     * Releases the buffer from the builder and holds it in the string object.
     */
    String::String( StringBuilder* string_builder )
    {
        length_ = string_builder->get_length();
        str_ = string_builder->release();
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
        if (length_ != 0) {
            free( str_ );
        }
    }

    /*
     * Get representation of C string.
     */
    const char* String::get_string( void ) const
    {
        return str_;
    }

    /*
     * Get length of the string.
     */
    size_t String::get_length( void ) const
    {
        return length_;
    }

}
