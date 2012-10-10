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
        Type get_character( size_t index ) const;
        virtual const Type* get_string( void ) const = 0;
        virtual size_t get_length( void ) const = 0;

        // String binary operations.
        bool is_equal( const JUTIL::BaseString<Type>* other ) const;

        // String searching.
        size_t find( Type character ) const;
        size_t find( Type character, size_t start ) const;
        size_t find( const JUTIL::BaseString<Type>* string ) const;
        size_t find( const JUTIL::BaseString<Type>* string, size_t start ) const;

    public:

        static const unsigned int INVALID_INDEX = 0xFFFFFFFF;

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
     * Get character at index.
     * Assumes valid index passed in.
     */
    template <class Type>
    Type BaseString<Type>::get_character( size_t index ) const
    {
        const Type* string = get_string();
        return string[ index ];
    }

    /*
     * Returns whether two strings are equal.
     */
    template <class Type>
    bool BaseString<Type>::is_equal( const JUTIL::BaseString<Type>* other ) const
    {
        // Check length for quick check.
        if (get_length() != other->get_length()) {
            return false;
        }

        // Loop through characters.
        size_t i;
        size_t length = get_length();
        for (i = 0; i < length; ++i) {
            if (get_character( i ) != other->get_character( i )) {
                return false;
            }
        }
        
        // No mismatch.
        return true;
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
    unsigned int BaseString<Type>::find( Type character, size_t start ) const
    {
        // Find the first index of character starting from start parameter.
        size_t i;
        for (i = start; i < get_length(); ++i) {
            if (get_character( i ) == character) {
                return i;
            }
        }

        return INVALID_INDEX;
    }

    /*
     * Find the first instance of a substring, if any.
     * Returns the index of the first character of found substring if found, INVALID_INDEX otherwise.
     */
    template <class Type>
    unsigned int BaseString<Type>::find( const JUTIL::BaseString<Type>* string ) const
    {
        return find( string, 0 );
    }

    /*
     * Find the first instance of a substring, if any.
     * Returns the index of the first character of found substring if found, INVALID_INDEX otherwise.
     */
    template <class Type>
    unsigned int BaseString<Type>::find( const JUTIL::BaseString<Type>* string, size_t start ) const
    {
        // Easy case if substring is larger than us.
        size_t our_length = get_length();
        size_t string_length = string->get_length();
        if (get_length() < string_length) {
            return INVALID_INDEX;
        }

        // Look for first index of first character in substring.
        size_t i;
        for (i = 0; i < our_length; ++i) {
            printf("Checking at %d = %c...\n", i, get_character(i));

            // Check if it's possible to fit at this point.
            size_t characters_left = (our_length - i);
            printf("Characters left: %d\n", characters_left);
            if (characters_left < string_length) {
                break;
            }

            // Search only if enough room.
            bool all_matched = true;
            size_t j;
            for (j = 0; j < string_length; ++j) {
                // Check matching character.
                printf("Comparing %c and %c.\n", get_character( i + j ), string->get_character( j ));
                if (get_character( i + j ) != string->get_character( j )) {
                    printf( "Mismatch.\n" );
                    all_matched = false;
                    break;
                }
            }

            // All matched, found pattern.
            if (all_matched) {
                return i;
            }
        }

        return INVALID_INDEX;
    }

}

#endif // BASE_STRING_HPP
