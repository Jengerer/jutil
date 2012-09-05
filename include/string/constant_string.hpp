#ifndef CONSTANT_STRING_HPP
#define CONSTANT_STRING_HPP

#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a C-string representation.
     * Does not manage string memory buffer.
     */
    class __declspec(dllexport) ConstantString : public BaseString
    {

    public:

        ConstantString( const char* string );
        ConstantString( const char* string, size_t length );
        virtual ~ConstantString( void );

        // Attribute functions.
        virtual const char* get_string( void ) const;

    private:

        const char* string_;
    
    };

}

#endif // CONSTANT_STRING_HPP
