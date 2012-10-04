#ifndef BASE_CONSTANT_STRING_HPP
#define BASE_CONSTANT_STRING_HPP

#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a string represenation.
     * Does not manage string memory buffer.
     */
    template <class Type>
    class __declspec(dllexport) BaseConstantString : public BaseString<Type>
    {

    public:

        // Constructors from string types.
        BaseConstantString( void );
        BaseConstantString( const Type* string, size_t length );
        BaseConstantString( const BaseString<Type>& string );
        virtual ~BaseConstantString( void );

        // String handling.
        virtual const Type* get_string( void ) const;
        virtual size_t get_length( void ) const;
        void set_string( const BaseString<Type>* other );
        void set_string( const Type* string, size_t length );

    private:

        const Type* string_;
        size_t length_;
    
    };

    /*
     * Constant string default constructor.
     */
    template <class Type>
    BaseConstantString<Type>::BaseConstantString( void )
    {
        string_ = nullptr;
        length_ = 0;
    }

    /*
     * Constant string constructor from string with length.
     */
    template <class Type>
    BaseConstantString<Type>::BaseConstantString( const Type* string, unsigned int length )
    {
        set_string( string, length );
    }

    /*
     * Constant string constructor from managed string.
     * Assumes managed string will out-live constant string usage.
     */
    template <class Type>
    BaseConstantString<Type>::BaseConstantString( const BaseString<Type>& string )
    {
        set_string( &string );
    }

    /*
     * Constant string destructor.
     */
    template <class Type>
    BaseConstantString<Type>::~BaseConstantString( void )
    {
        // We're not managing string, so don't delete.
    }

    /*
     * Get constant string pointer.
     */
    template <class Type>
    const Type* BaseConstantString<Type>::get_string( void ) const
    {
        return string_;
    }

    /*
     * Get string length.
     */
    template <class Type>
    size_t BaseConstantString<Type>::get_length( void ) const
    {
        return length_;
    }

    /*
     * String handle updating by base string.
     */
    template <class Type>
    void BaseConstantString<Type>::set_string( const BaseString<Type>* other )
    {
        set_string( other->get_string(), other->get_length() );
    }

    /*
     * String handle updating by string and length.
     */
    template <class Type>
    void BaseConstantString<Type>::set_string( const Type* string, size_t length )
    {
        string_ = string;
        length_ = length;
    }

}

#endif // BASE_CONSTANT_STRING_HPP
