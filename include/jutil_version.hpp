#ifndef JUTIL_VERSION_HPP
#define JUTIL_VERSION_HPP

#include <string/string.hpp>

namespace JUTIL
{
	// Get current JUTIL version string.
	_declspec(dllexport) const JUTIL::String* get_version_string( void );
}

#endif // JUTIL_VERSION_HPP