#ifndef BASE_STRING_HPP
#define BASE_STRING_HPP

namespace JUTIL
{

    /*
     * Abstract string class.
     */
    class __declspec(dllexport) BaseString
    {

    public:

        // Generic string constructor.
        virtual ~BaseString( void );

        // Common string getters.
        virtual const char* get_string( void ) const = 0;
        unsigned int get_length( void ) const;

    protected:

        // String length modifier.
        void set_length( unsigned int length );

    private:

        // String length.
        int length_;

    };

}

#endif // BASE_STRING_HPP
