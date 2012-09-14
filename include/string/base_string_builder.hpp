#ifndef BASE_STRING_BUILDER_HPP
#define BASE_STRING_BUILDER_HPP

#include <string.h>
#include "memory/array_builder.hpp"

namespace JUTIL
{

    /*
     * Class for handling a generic string buffer.
     */
    template <class Type>
    class __declspec(dllexport) BaseStringBuilder
    {

    public:

        BaseStringBuilder( void );
        ~BaseStringBuilder( void );

        // Buffer managing functions.
        void set_string( Type* string, size_t length );
        Type* release( void );
        void clear( void );
        
        // Buffer reading functions.
        const Type* get_string( void ) const;
        size_t get_length( void ) const;

    private:

        // Buffer handling.
        const Type* set_string( const Type* string );
        bool set_length( size_t length );

    protected:

        ArrayBuilder<Type> builder_;

    };

    /*
     * Default string constructor; empty.
     */
    template <class Type>
    BaseStringBuilder<Type>::BaseStringBuilder( void )
    {
        // Nothing.
    }

    /*
     * StringBuilder buffer destructor.
     */
    template <class Type>
    BaseStringBuilder<Type>::~BaseStringBuilder( void )
    {
        clear();
    }

    /*
     * Set string buffer managed by builder.
     * Assumes previous buffer has been released or cleared, if any.
     */
    template <class Type>
    void BaseStringBuilder<Type>::set_string( Type* string, size_t length )
    {
        string_ = string;
        length_ = length;
    }

    /*
     * Release handle to memory for outer source to manage.
     */
    template <class Type>
    Type* BaseStringBuilder<Type>::release( void )
    {
        return builder_.release();
    }

    /*
     * Clear the string buffer, if not empty.
     */
    template <class Type>
    void BaseStringBuilder<Type>::clear( void )
    {
        builder_.clear();
    }

    /*
     * Get a pointer to the current string.
     * Returns nullptr if no string exists yet.
     */
    template <class Type>
    const Type* BaseStringBuilder<Type>::get_string( void ) const
    {
        return builder_.get_array();
    }

    /*
     * Gets the length of the string, not including the null character.
     */
    template <class Type>
    size_t BaseStringBuilder<Type>::get_length( void ) const
    {
        return builder_.get_size();
    }

    /*
     * Sets the string contained by the buffer. Buffer is resized if needed.
     * Returns the new string contained in buffer if successful, nullptr otherwise.
     */
    template <class Type>
    const Type* BaseStringBuilder<Type>::set_string( const Type* string )
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
    bool BaseStringBuilder<Type>::set_length( size_t length )
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

#endif // BASE_STRING_BUILDER_HPP
