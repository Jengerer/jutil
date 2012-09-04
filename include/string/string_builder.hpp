#ifndef STRING_BUILDER_HPP
#define STRING_BUILDER_HPP

#include <string.h>

namespace JUTIL
{

    /*
     * Class for handling a C-style string buffer.
     */
    class __declspec(dllexport) StringBuilder
    {

    public:

        StringBuilder( void );
        ~StringBuilder( void );

        // Buffer managing functions.
        const char* write( const char* format, ... );
        char* release( void );
        void clear( void );
        
        // Buffer reading functions.
        const char* get_string( void ) const;
        size_t get_length( void ) const;

    private:

        // Buffer handling.
        const char* set_string( const char* string );
        bool set_length( size_t length );

    private:

        char* string_;
        size_t length_;

    };

}

#endif // STRING_BUILDER_HPP
