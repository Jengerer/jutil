#include <jutil_version.hpp>

namespace JUTIL
{
	// Version string to return.
	const ConstantString JUTIL_VERSION( "0.1.7" );

	/*
	 * Return the current version string.
	 */
	const JUTIL::String* get_version_string( void )
	{
		return &JUTIL_VERSION;
	}
}