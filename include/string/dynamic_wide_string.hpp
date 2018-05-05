#ifndef DYNAMIC_WIDE_STRING_HPP
#define DYNAMIC_WIDE_STRING_HPP

#include "string/base_dynamic_string.hpp"

namespace JUTIL
{

	/*
	 * String container class that wraps a wide character string representation.
	 * Assumes string is writable; frees memory on destruction.
	 */
	class DynamicWideString : public BaseDynamicString<wchar_t>
	{

	public:

		JUTIL_API DynamicWideString( void );
		JUTIL_API DynamicWideString( wchar_t* string, size_t length );
		virtual JUTIL_API ~DynamicWideString( void );

		// Buffer management.
		JUTIL_API bool write( const wchar_t* format, ... );
		JUTIL_API bool write( const wchar_t* format, va_list args );

	};

}

#endif // DYNAMIC_WIDE_STRING_HPP
