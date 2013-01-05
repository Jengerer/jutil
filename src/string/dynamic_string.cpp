#include "string/dynamic_string.hpp"
#include "memory/base_allocator.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace JUTIL
{

	/*
	 * String constructor from string builder.
	 * Releases the buffer from the builder and holds it in the string object.
	 */
	DynamicString::DynamicString( void )
		: BaseDynamicString<char>()
	{
	}

	/*
	 * String constructor from string and length.
	 * Does not assume string is null-terminated; does not terminate it itself.
	 */
	DynamicString::DynamicString( char* string, size_t length )
		: BaseDynamicString<char>( string, length )
	{
	}

	/*
	 * String destructor (already cleared by base dynamic).
	 */
	DynamicString::~DynamicString( void )
	{
	}

	/*
	 * Write formatted string output to the buffer.
	 * Returns a pointer to the new string if succeeded, nullptr otherwise.
	 */
	bool DynamicString::write( const char* format, ... )
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
	bool DynamicString::write( const char* format, va_list args )
	{
		// Get needed size.
		// Keep old args for actual write.
		va_list new_args = args;
		int length = vsnprintf( nullptr, 0, format, args );

		// Allocate new string size.
		size_t old_length = get_length();
		size_t added_length = length;
		size_t new_length = old_length + added_length;
		if ((length < 0) || !set_length( new_length )) {
			return false;
		}

		// Write to buffer.
		char* new_string = builder_.get_array();
		int written = vsnprintf( new_string + old_length, added_length, format, new_args );
		va_end( new_args );
		if (written < 0) {
			return false;
		}
		return true;
	}

}
