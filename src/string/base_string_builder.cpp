#include "string/string_builder.hpp"
#include "memory/base_allocator.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace JUTIL
{

    /*
     * Default string constructor; empty.
     */
    template <class Type>
    BaseStringBuilder::BaseStringBuilder( void )
    {
        // Nothing.
    }

    /*
     * StringBuilder buffer destructor.
     */
    template <class Type>
    BaseStringBuilder::~BaseStringBuilder( void )
    {
        clear();
    }

    /*
     * Write formatted string output to the buffer.
     * Returns a pointer to the new string if succeeded, nullptr otherwise.
     */
    template <class Type>
    const Type* BaseStringBuilder::write( const Type* format, ... )
    {
        // Get needed size.
        va_list args;
        va_start( args, format );
        write( format, args );
        va_end( args );
        return string_;
    }

    /*
     * Set string buffer managed by builder.
     * Assumes previous buffer has been released or cleared, if any.
     */
    template <class Type>
    void BaseStringBuilder::set_string( Type* string, size_t length )
    {
        string_ = string;
        length_ = length;
    }

    /*
     * Write formatted string output to buffer with variable arguments.
     * Returns a pointer to the new string if succeeded, nullptr otherwise.
     * Assumes 'args' list has been started.
     */
    template <class Type>
    const Type* BaseStringBuilder::write( const Type* format, va_list args )
    {
        // Get needed size.
        int length = vsnprintf( nullptr, 0, format, args );
        va_end( args );

        // Allocate new string size.
        size_t old_length = length_;
        if ((length < 0) || !set_length( old_length + length )) {
            return nullptr;
        }

        // Write to buffer.
        va_start( args, format );
        int written = vsnprintf( string_ + old_length, length + 1, format, args );
        if (written < 0) {
            return nullptr;
        }
        return string_;
    }

    /*
     * Release handle to memory for outer source to manage.
     */
    template <class Type>
    Type* BaseStringBuilder::release( void )
    {
        if (length_ != 0) {
            Type* temp = string_;
            string_ = nullptr;
            length_ = 0;
            return temp;
        }

        return nullptr;
    }

    /*
     * Clear the string buffer, if not empty.
     */
    template <class Type>
    void BaseStringBuilder::clear( void )
    {
        if (length_ != 0) {
            BaseAllocator::release( string_ );
            string_ = nullptr;
            length_ = 0;
        }
    }

    /*
     * Get a pointer to the current string.
     * Returns nullptr if no string exists yet.
     */
    template <class Type>
    const Type* BaseStringBuilder::get_string( void ) const
    {
        return string_;
    }

    /*
     * Gets the length of the string, not including the null character.
     */
    template <class Type>
    size_t BaseStringBuilder::get_length( void ) const
    {
        return length_;
    }

    /*
     * Sets the string contained by the buffer. Buffer is resized if needed.
     * Returns the new string contained in buffer if successful, nullptr otherwise.
     */
    template <class Type>
    const Type* BaseStringBuilder::set_string( const Type* string )
    {
        size_t length = strlen( string );
        if (length_ != length) {
            // Attempt resize.
            if (!set_length( length )) {
                return nullptr;
            }
        }

        // Copy new string.
        memcpy( string_, string, length + 1 );
        return string_;
    }

    /*
     * Set new buffer length (excluding null character).
     * Returns true if resizing succeeded, false otherwise.
     */
    template <class Type>
    bool BaseStringBuilder::set_length( size_t length )
    {
        // Attempt allocation/resize.
        size_t new_size = length + 1;
        bool result;
        if (length_ == 0) {
            result = BaseAllocator::allocate_array( &string_, new_size );
        }
        else {
            result = BaseAllocator::reallocate_array( &string_, new_size );
        }

        // Return false if failed to size.
        if (!result) {
            return false;
        }

        // Update and finish.
        length_ = length;
        return true;
    }

}
