#ifndef STRING_HASHER_HPP
#define STRING_HASHER_HPP

#include <string/string.hpp>
#include <ctype.h>

#include <string/md5.hpp>


namespace JUTIL
{

	/*
	 * String hasher class, essentially a clone of java.lang.String.hashCode algorithm.
	 */
	class StringHasher
	{

	public:

		// Inspired by the java.lang.String.hashCode() algorithm.
		static unsigned int hash( const String* input )
		{
			unsigned int result = 0;
			const char* str = input->get_string();

			// Hash characters.
			size_t i;
			size_t length = input->get_length();
			for (i = 0; i < length; i++) {
				result = 31 * result + tolower(str[i]);
			}

			return result;
		}
		
		static const unsigned int MD5_HASH_SIZE = JUTIL::MD5::HASH_SIZE;
 
		static void md5( const String* input, uint8_t* result ) {
			JUTIL::MD5::MD5_CTX mdContext;
			JUTIL::MD5::MD5Init (&mdContext);
			JUTIL::MD5::MD5Update (&mdContext, (const unsigned char *)input->get_string(), input->get_length());
			JUTIL::MD5::MD5Final (&mdContext);
			for( int i = 0; i < MD5_HASH_SIZE; ++i){
				result[i] = mdContext.digest[i];
			}
		}
	};

}

#endif // STRING_HASHER_HPP