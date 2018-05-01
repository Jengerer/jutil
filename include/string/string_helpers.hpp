#ifndef STRING_HELPERS_HPP
#define STRING_HELPERS_HPP

#include "base/jutil_base.hpp"
#include <cstdint>
#include <string/constant_string.hpp>

namespace JUTIL
{
	// Convert a string to a 32-bit unsigned integer.
	bool JUTIL_API string_to_unsigned_32( const JUTIL::ConstantString& string, uint32_t& result );

	// Convert a string to a 32-bit unsigned integer.
	bool JUTIL_API string_to_unsigned_64( const JUTIL::ConstantString& string, uint64_t& result );

	// Convert a string to an floating point value.
	float JUTIL_API string_to_float( const JUTIL::ConstantString& string );
}

#endif // STRING_HELPERS_HPP