#include "string/dynamic_wide_string.hpp"
#include "memory/base_allocator.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace JUTIL
{

	/*
	 * String constructor from string builder.
	 * Releases the buffer from the builder and holds it in the string object.
	 */
	DynamicWideString::DynamicWideString( void )
		: BaseDynamicString<wchar_t>()
	{
	}

	/*
	 * String constructor from string and length.
	 * Does not assume string is null-terminated; does not terminate it itself.
	 */
	DynamicWideString::DynamicWideString( wchar_t* string, size_t length )
		: BaseDynamicString<wchar_t>( string, length )
	{
	}

	/*
	 * String destructor (already cleared by base dynamic).
	 */
	DynamicWideString::~DynamicWideString( void )
	{
	}

	/*
	 * Write formatted string output to the buffer.
	 * Returns a pointer to the new string if succeeded, nullptr otherwise.
	 */
	bool DynamicWideString::write( const wchar_t* format, ... )
	{
		// Get needed size.
		va_list args;
		va_start( args, format );
		if (!write( format, args )) {
			return false;
		}
		va_end( args );
		return true;
	}

	/*
	 * Write formatted string output to buffer with variable arguments.
	 * Returns a pointer to the new string if succeeded, nullptr otherwise.
	 * Assumes 'args' list has been started.
	 */
	bool DynamicWideString::write( const wchar_t* format, va_list args )
	{
		// Get needed size.
		// Keep old args for actual write.
		va_list new_args = args;
		int length = _vscwprintf( format, args );

		// Allocate new string size.
		size_t old_length = get_length();
		size_t added_length = length;
		size_t new_length = old_length + added_length;
		if ((length < 0) || !set_length( new_length )) {
			return false;
		}

		// Write to buffer.
		wchar_t* new_string = builder_.get_array();
		int written = _vsnwprintf_s( new_string + old_length, added_length + 1, added_length, format, new_args );
		va_end( new_args );
		if (written < 0) {
			return false;
		}
		return true;
	}

}
