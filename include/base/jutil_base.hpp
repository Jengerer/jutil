#ifndef JUTIL_BASE_HPP
#define JUTIL_BASE_HPP

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