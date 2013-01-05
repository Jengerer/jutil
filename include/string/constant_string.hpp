#ifndef CONSTANT_STRING_HPP
#define CONSTANT_STRING_HPP

#include "string/base_constant_string.hpp"

namespace JUTIL
{

	/*
	 * Constant string representation for C-style character array.
	 */
	class __declspec(dllexport) ConstantString : public BaseConstantString<char>
	{

	public:

		// Constructors from C-style string types.
		ConstantString( void );
		ConstantString( const char* string );
		ConstantString( const char* string, size_t length );
		ConstantString( const BaseString<char>* string );
		virtual ~ConstantString( void );

	};

}

#endif // CONSTANT_STRING_HPP