#ifndef BASE_DYNAMIC_STRING_HPP
#define BASE_DYNAMIC_STRING_HPP

#include <string.h>
#include "memory/array_builder.hpp"
#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * Class for handling a generic string buffer.
     */
    template <class Type>
    class __declspec(dllexport) BaseDynamicString : public BaseString<Type>
    {

    public:

        BaseDynamicString( void );
        BaseDynamicString( Type* string, size_t length );
        ~BaseDynamicString( void );

        // Buffer managing functions.
        bool copy( const BaseString<Type>* string );
        bool copy( const Type* string, size_t length );
        void set_string( Type* string, size_t length );
        Type* release( void );
        void clear( void );
        
        // Buffer reading functions.
        Type* get_string( void );
        virtual const Type* get_string( void ) const;
        virtual size_t get_length( void ) const;

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
    BaseDynamicString<Type>::BaseDynamicString( void )
    {
        // Nothing.
    }

    /*
     * Constructor from existing buffer.
     */
    template <class Type>
    BaseDynamicString<Type>::BaseDynamicString( Type* string, size_t length )
    {
        set_string( string, length );
    }

    /*
     * StringBuilder buffer destructor.
     */
    template <class Type>
    BaseDynamicString<Type>::~BaseDynamicString( void )
    {
        clear();
    }

    /*
     * Copy from base string to buffer.
     */
    template <class Type>
    bool BaseDynamicString<Type>::copy( const BaseString<Type>* string )
    {
        return copy( string->get_string(), string->get_length() );
    }

    /*
     * Copy raw string to buffer.
     */
    template <class Type>
    bool BaseDynamicString<Type>::copy( const Type* string, size_t length )
    {
        // Copy memory.
        size_t size = length + 1;
        if (!builder_.set_size( size )) {
            return false;
        }
        memcpy( builder_.get_array(), string, size );
        return true;
    }

    /*
     * Set string buffer managed by builder.
     * Assumes previous buffer has been released or cleared, if any.
     */
    template <class Type>
    void BaseDynamicString<Type>::set_string( Type* string, size_t length )
    {
        builder_.set_array( string, length );
    }

    /*
     * Release handle to memory for outer source to manage.
     */
    template <class Type>
    Type* BaseDynamicString<Type>::release( void )
    {
        return builder_.release();
    }

    /*
     * Clear the string buffer, if not empty.
     */
    template <class Type>
    void BaseDynamicString<Type>::clear( void )
    {
        builder_.clear();
    }

    /*
     * Get a pointer to the string buffer.
     * Returns nullptr if no string exists yet.
     */
    template <class Type>
    Type* BaseDynamicString<Type>::get_string( void )
    {
        return builder_.get_array();
    }

    /*
     * Get a pointer to the current string.
     * Returns nullptr if no string exists yet.
     */
    template <class Type>
    const Type* BaseDynamicString<Type>::get_string( void ) const
    {
        return builder_.get_array();
    }

    /*
     * Gets the length of the string, not including the null character.
     */
    template <class Type>
    size_t BaseDynamicString<Type>::get_length( void ) const
    {
        return builder_.get_size();
    }

    /*
     * Set new buffer length (excluding null character).
     * Returns true if resizing succeeded, false otherwise.
     */
    template <class Type>
    bool BaseDynamicString<Type>::set_length( size_t length )
    {
        // Attempt allocation/resize.
        size_t new_size = length + 1;
        if (!builder_.set_size( new_size )) {
            return false;
        }
        return true;
    }

}

#endif // BASE_DYNAMIC_STRING_HPP