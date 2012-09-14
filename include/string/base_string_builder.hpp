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
        const Type* write( const Type* format, ... );
        const Type* write( const Type* format, va_list args );
        Type* release( void );
        void clear( void );
        
        // Buffer reading functions.
        const char* get_string( void ) const;
        size_t get_length( void ) const;

    private:

        // Buffer handling.
        const Type* set_string( const Type* string );
        bool set_length( size_t length );

    protected:

        ArrayBuilder<Type> builder_;

    };

}

#endif // BASE_STRING_BUILDER_HPP
