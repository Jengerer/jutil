#ifndef JUTIL_BASE_HPP
#define JUTIL_BASE_HPP

// Set importing when using.
#if !defined( JUTIL_API )
#define JUTIL_API __declspec(dllimport)
#endif

namespace JUTIL
{

    /*
     * Base class for general utilities.
     */
    class __declspec(dllexport) JUTILBase
    {

    public:

        // Debugging functions.
        static void debug_assert( bool condition );

    };

}

#endif // JUTIL_BASE_HPP