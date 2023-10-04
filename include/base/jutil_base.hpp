#ifndef JUTIL_BASE_HPP
#define JUTIL_BASE_HPP

// Set importing when using.
#if defined(JUTIL_DLL)
#if defined(JUTIL_EXPORT)
#define JUTIL_API __declspec(dllexport)
#else
#define JUTIL_API __declspec(dllimport)
#endif
#else
#define JUTIL_API
#endif

namespace JUTIL
{

	/*
	 * Base class for general utilities.
	 */
	class JUTIL_API JUTILBase
	{

	public:

		// Debugging functions.
		static void debug_assert( bool condition );

	};

}

#endif // JUTIL_BASE_HPP