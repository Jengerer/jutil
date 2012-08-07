#include "string_builder.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*
 * Default string constructor; empty.
 */
StringBuilder::StringBuilder( void )
{
	string_ = nullptr;
	length_ = 0;
}

/*
 * StringBuilder buffer destructor.
 */
StringBuilder::~StringBuilder( void )
{
	clear();
}

/*
 * Write formatted string output to the buffer.
 * Returns a pointer to the new string if succeeded, nullptr otherwise.
 */
const char* StringBuilder::write( const char* format, ... )
{
	// Get needed size.
	va_list args;
	va_start( args, format );
	int length = vsnprintf( nullptr, 0, format, args );
	va_end( args );

	// Allocate new string size.
	size_t old_length = length_;
	if ((length < 0) || !set_length( old_length + length )) {
		return nullptr;
	}

	// Write to buffer.
	va_start( args, format );
	int written = vsnprintf( string_ + old_length, length + 1, format, args );
	if (written < 0) {
		return nullptr;
	}
	va_end( args );
	return string_;
}

/*
 * Clear the string buffer, if not empty.
 */
void StringBuilder::clear( void )
{
	if (length_ != 0) {
		free( string_ );
		string_ = nullptr;
		length_ = 0;
	}
}

/*
 * Get a pointer to the current string.
 * Returns nullptr if no string exists yet.
 */
const char* StringBuilder::get_string( void ) const
{
	return string_;
}

/*
 * Gets the length of the string, not including the null character.
 */
size_t StringBuilder::get_length( void ) const
{
	return length_;
}

/*
 * Sets the string contained by the buffer. Buffer is resized if needed.
 * Returns the new string contained in buffer if successful, nullptr otherwise.
 */
const char* StringBuilder::set_string( const char* string )
{
	size_t length = strlen( string );
	if (length_ != length) {
		// Attempt resize.
		if (!set_length( length )) {
			return nullptr;
		}
	}

	// Copy new string.
	memcpy( string_, string, length + 1 );
	return string_;
}

/*
 * Set new buffer length (excluding null character);
 * Returns true if resizing succeeded, false otherwise.
 */
bool StringBuilder::set_length( size_t length )
{
	// Attempt allocation/resize.
	char* new_string;
	size_t new_size = length + 1;
	if (length_ == 0) {
		new_string = (char*)malloc( new_size );
	}
	else {
		new_string = (char*)realloc( string_, new_size );
	}

	// Return false if failed to size.
	if (new_string == nullptr) {
		return false;
	}

	// Update and finish.
	string_ = new_string;
	length_ = length;
	return true;
}