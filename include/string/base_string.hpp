#ifndef BASE_STRING_HPP
#define BASE_STRING_HPP

namespace JUTIL
{

    /*
     * Abstract string class.
     */
    template <class Type>
    class __declspec(dllexport) BaseString
    {

    public:

        // Generic string constructor.
        virtual ~BaseString( void );

        // Common string getters.
        virtual const Type* get_string( void ) const = 0;
        unsigned int get_length( void ) const;

    protected:

        // String length modifier.
        void set_length( unsigned int length );

    private:

        // String length.
        unsigned int length_;

    };

    /*
     * Generic string destructor.
     */
    template <class Type>
    BaseString<Type>::~BaseString( void )
    {
        // Nothing to clean yet.
    }

    /*
     * Get string length.
     */
    template <class Type>
    unsigned int BaseString<Type>::get_length( void ) const
    {
        return length_;
    }

    /*
     * Set stored string length.
     */
    template <class Type>
    void BaseString<Type>::set_length( unsigned int length )
    {
        length_ = length;
    }


}

#endif // BASE_STRING_HPP
