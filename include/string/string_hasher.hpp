#ifndef STRING_HASHER_HPP
#define STRING_HASHER_HPP

#include <string/string.hpp>
#include <ctype.h>

namespace JUTIL
{

    /*
     * String hasher class, essentially a clone of java.lang.String.hashCode algorithm.
     */
    class StringHasher
    {

    public:

	    // Inspired by the java.lang.String.hashCode() algorithm.
        static unsigned int hash( const ConstantString& input )
        {
            unsigned int result = 0;
            const char* str = input.get_string();

            // Hash characters.
            unsigned int i;
            for (i = 0; i < input.get_length(); i++) {
                result = 31 * result + tolower(str[i]);
		    }

		    return result;
	    }

    };

}

#endif // STRING_HASHER_HPP