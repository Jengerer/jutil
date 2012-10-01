#ifndef CONSTANT_WIDE_STRING_HPP
#define CONSTANT_WIDE_STRING_HPP

#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * String container class that wraps a C-string representation.
     * Does not manage string memory buffer.
     */
    class __declspec(dllexport) ConstantWideString : public BaseString<wchar_t>
    {

    public:

        // Constructors from string types.
        ConstantWideString( void );
        ConstantWideString( const wchar_t* string );
        ConstantWideString( const BaseString<wchar_t>& string );
        ConstantWideString( const wchar_t* string, size_t length );
        virtual ~ConstantWideString( void );

        // String handling.
        virtual const wchar_t* get_string( void ) const;
        void set_string( const BaseString<wchar_t>* other );
        void set_string( const wchar_t* string );
        void set_string( const wchar_t* string, unsigned int length );

    private:

        const wchar_t* string_;
    
    };

}

#endif // CONSTANT_WIDE_STRING_HPP
