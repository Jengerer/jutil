#include "string/wide_string_builder.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace JUTIL
{

    /*
     * Default string constructor; empty.
     */
    WideStringBuilder::WideStringBuilder( void )
    {
        // Nothing special.
    }

    /*
     * WideStringBuilder buffer destructor.
     */
    WideStringBuilder::~WideStringBuilder( void )
    {
        // Nothing special.
    }

    /*
     * Write formatted string output to the buffer.
     * Returns a pointer to the new string if succeeded, nullptr otherwise.
     */
    const wchar_t* WideStringBuilder::write( const wchar_t* format, ... )
    {
        // Get needed size.
        va_list args;
        va_start( args, format );
        write( format, args );
        va_end( args );
        return builder_.get_array();
    }

    /*
     * Write formatted string output to buffer with variable arguments.
     * Returns a pointer to the new string if succeeded, nullptr otherwise.
     * Assumes 'args' list has been started.
     */
    const wchar_t* WideStringBuilder::write( const wchar_t* format, va_list args )
    {
        // Get needed size.
        int length = _vsnwprintf( nullptr, 0, format, args );
        va_end( args );

        // Allocate new string size.
        size_t old_length = builder_.get_size();
        if ((length < 0) || !builder_.set_size( old_length + length )) {
            return nullptr;
        }

        // Write to buffer.
        wchar_t* new_string = builder_.get_array();
        va_start( args, format );
        int written = _vsnwprintf( new_string + old_length, length + 1, format, args );
        if (written < 0) {
            return nullptr;
        }
        return new_string;
    }

}
