#ifndef STRING_HPP
#define STRING_HPP

#include <string.h>

/*
 * Class for handling a C-style string buffer.
 */
class String
{

public:

	String( void );
	~String( void );

	// Buffer managing functions.
	const char* write( const char* format, ... );
	void clear( void );
	
	// Buffer reading functions.
	const char* get_string( void ) const;
	size_t get_length( void ) const;

private:

	// Buffer handling.
	const char* set_string( const char* string );
	bool set_length( size_t length );

private:

	char* string_;
	size_t length_;

};

#endif // STRING_HPP