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
        const Type* copy( const Type* string, size_t length );
        void set_string( Type* string, size_t length );
        Type* release( void );
        void clear( void );
        
        // Buffer reading functions.
        const Type* get_string( void ) const;
        size_t get_length( void ) const;

    private:

        // Buffer handling.
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
     * Copy raw string to builder.
     */
    template <class Type>
    const Type* BaseStringBuilder<Type>::copy( const Type* string, size_t length )
    {
        // Resize if necessary.
        size_t size = length + 1;
        if (builder_.get_size() < length) {
            if (!builder_.set_size( size )) {
                return nullptr;
            }
        }

        // Copy.
        memcpy( builder_.get_array(), string, size );
        return get_string();
    }

    /*
     * Set string buffer managed by builder.
     * Assumes previous buffer has been released or cleared, if any.
     */
    template <class Type>
    void BaseStringBuilder<Type>::set_string( Type* string, size_t length )
    {
        builder_.set_array( string, length );
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
     * Set new buffer length (excluding null character).
     * Returns true if resizing succeeded, false otherwise.
     */
    template <class Type>
    bool BaseStringBuilder<Type>::set_length( size_t length )
    {
        // Attempt allocation/resize.
        size_t new_size = length + 1;
        if (!builder_.set_size( new_size )) {
            return false;
        }

        // Update and finish.
        length_ = length;
        return true;
    }

}

#endif // BASE_STRING_BUILDER_HPP
