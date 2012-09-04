#ifndef STRING_HPP
#define STRING_HPP

namespace JUTIL
{

    /*
     * String container class that just tracks the string.
     * Base class that does not make assumption about usage of buffer;
     * does NOT delete string on removal.
     */
    class String
    {

    public:

        String( void );
        String( char* str );
        String( char* str, size_t length );
        ~String( void );

        // String management.
        bool copy( const char* other, size_t length );

        // Attribute functions.
        const char* get_string( void ) const;
        size_t get_length( void ) const;

    protected:

        char* str_;
        size_t length_;
    
    };

}

#endif // STRING_HPP
