#include "string/string_helpers.hpp"
#include <cmath>

namespace JUTIL
{

	// Convert a string to 32-bit unsigned integer.
	bool string_to_unsigned_32( const JUTIL::ConstantString& string, uint32_t& result )
	{
		const size_t length = string.get_length();
		if (length == 0) {
			return false;
		}

		uint32_t value = 0;
		const char* raw = string.get_string();
		for (size_t i = 0; i < length; ++i) {
			const char current_character = raw[i];
			if ((current_character < '0') || (current_character > '9')) {
				return false;
			}
			const uint32_t digit = static_cast<uint32_t>(current_character - '0');
			value = (value * 10) + digit;
		}

		result = value;
		return(true);
	}

	// Convert a string to 64-bit unsigned integer.
	bool string_to_unsigned_64( const JUTIL::ConstantString& string, uint64_t& result )
	{
		const size_t length = string.get_length();
		if (length == 0) {
			return false;
		}

		uint64_t value = 0;
		const char* raw = string.get_string();
		for (size_t i = 0; i < length; ++i) {
			const char current_character = raw[i];
			if ((current_character < '0') || (current_character > '9')) {
				return false;
			}
			const uint64_t digit = static_cast<uint64_t>(current_character - '0');
			value = (value * 10) + digit;
		}

		result = value;
		return(true);
	}

	// Convert a string to floating point value.
	bool string_to_float( const JUTIL::ConstantString& string, float& result )
	{
		const size_t length = string.get_length();
		if (length == 0) {
			return false;
		}
		
		float sign = 1.f;
		float fractional_digits = 0.f;
		uint64_t whole_value = 0;
		uint64_t fractional_value = 0;
		const char* raw = string.get_string();

		// Build whole part
		size_t i;
		for (i = 0; i < length; ++i) {
			const char current_character = raw[i];
			if ((i == 0) && (current_character == '-')) {
				sign = -1.f;
			}
			else if (current_character == '.') {
				break;
			}
			else if ((current_character < '0') || (current_character > '9')) {
				return false;
			}
			const uint64_t digit = static_cast<uint64_t>(current_character - '0');
			whole_value = (whole_value * 10) + digit;
		}

		// Build fractional part
		for (i = i + 1; i < length; ++i) {
			const char current_character = raw[i];
			if ((current_character < '0') || (current_character > '9')) {
				return false;
			}
			const uint64_t digit = static_cast<uint64_t>(current_character - '0');
			fractional_value = (fractional_value * 10) + digit;
			++fractional_digits;
		}

		// Build result
		const float whole_part = static_cast<float>(whole_value);
		const float fractional_numerator = static_cast<float>(fractional_value);
		const float fractional_denominator = std::powf(10.f, static_cast<float>(fractional_digits));
		result = sign * (whole_part + (fractional_numerator / fractional_denominator));
		return(true);
	}

}
