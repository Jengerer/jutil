#ifndef DYNAMIC_STRING_HPP
#define DYNAMIC_STRING_HPP

#include "string/base_dynamic_string.hpp"

namespace JUTIL
{

	/*
	 * String container class that wraps a C-string representation.
	 * Assumes string is writable; frees memory on destruction.
	 */
	class DynamicString : public BaseDynamicString<char>
	{

	public:

		JUTIL_API DynamicString( void );
		JUTIL_API DynamicString( char* string, size_t length );
		virtual JUTIL_API ~DynamicString( void );

		// Buffer management.
		JUTIL_API bool write( const char* format, ... );
		JUTIL_API bool vwrite( const char* format, va_list args );
	
	};

}

#endif // DYNAMIC_STRING_HPP
