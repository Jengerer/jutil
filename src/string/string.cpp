#include "string/string.hpp"
#include "memory/base_allocator.hpp"
#include <string.h>
#include <stdio.h>

namespace JUTIL
{

    /*
     * String constructor from string builder.
     * Releases the buffer from the builder and holds it in the string object.
     */
    String::String( StringBuilder* string_builder )
    {
        set_length( string_builder->get_length() );
        string_ = string_builder->release();
    }

    /*
     * String constructor from string and length.
     * Does not assume string is null-terminated; does not terminate it itself.
     */
    String::String( char* string, size_t length )
    {
        set_length( length );
        string_ = string;
    }

    /*
     * String destructor.
     */
    String::~String( void )
    {
        if (get_length() != 0) {
            BaseAllocator::release( string_ );
        }
    }

    /*
     * Get representation of C string.
     */
    const char* String::get_string( void ) const
    {
        return string_;
    }

}
