#include "string/wide_string.hpp"
#include "memory/base_allocator.hpp"
#include <string.h>
#include <stdio.h>

namespace JUTIL
{

    /*
     * String constructor from string builder.
     * Releases the buffer from the builder and holds it in the string object.
     */
    WideString::WideString( WideStringBuilder* string_builder )
    {
        set_length( string_builder->get_length() );
        string_ = string_builder->release();
    }

    /*
     * String constructor from string and length.
     * Does not assume string is null-terminated; does not terminate it itself.
     */
    WideString::WideString( wchar_t* string, size_t length )
    {
        set_length( length );
        string_ = string;
    }

    /*
     * String destructor.
     */
    WideString::~WideString( void )
    {
        if (get_length() != 0) {
            BaseAllocator::release( string_ );
        }
    }

    /*
     * Get representation of C string.
     */
    wchar_t* WideString::get_string( void )
    {
        return string_;
    }

    /*
     * Get representation of wide string.
     */
    const wchar_t* WideString::get_string( void ) const
    {
        return string_;
    }

}
