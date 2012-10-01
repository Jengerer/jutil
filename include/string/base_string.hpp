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

        // String searching.
        unsigned int find( Type character ) const;
        unsigned int find( Type character, unsigned int start ) const;

    public:

        static const unsigned int INVALID_INDEX = 0xFFFFFFFF;

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
     * Find the first instance of a character.
     * Returns the index of the character if found, INVALID_INDEX otherwise.
     */
    template <class Type>
    unsigned int BaseString<Type>::find( Type character ) const
    {
        return find( character, 0 );
    }

    /*
     * Find the first instance of a character from the given index.
     * Returns the index of the character if found, INVALID_INDEX otherwise.
     */
    template <class Type>
    unsigned int BaseString<Type>::find( Type character, unsigned int start ) const
    {
        // Find the first index of character starting from start parameter.
        unsigned int i;
        const Type* string = get_string();
        for (i = start; i < get_length(); ++i) {
            if (string[i] == character) {
                return i;
            }
        }

        return INVALID_INDEX;
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
