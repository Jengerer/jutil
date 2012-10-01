#ifndef CONSTANT_STRING_HPP
#define CONSTANT_STRING_HPP

#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a C-string representation.
     * Does not manage string memory buffer.
     */
    class __declspec(dllexport) ConstantString : public BaseString<char>
    {

    public:

        // Constructors from string types.
        ConstantString( void );
        ConstantString( const char* string );
        ConstantString( const char* string, size_t length );
        ConstantString( const BaseString<char>& string );
        virtual ~ConstantString( void );

        // String handling.
        virtual const char* get_string( void ) const;
        void set_string( const BaseString<char>* other );
        void set_string( const char* string );
        void set_string( const char* string, unsigned int length );

    private:

        const char* string_;
    
    };

}

#endif // CONSTANT_STRING_HPP
