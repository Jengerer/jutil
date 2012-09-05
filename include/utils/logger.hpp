#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>
#include "string/constant_string.hpp"

namespace JUTIL
{

    /*
     * Class to log text to a file.
     */
    class Logger
    {

    public:

        Logger( void );
        ~Logger( void );

        // File handling.
        bool open( const ConstantString& filename );
        void close( void );

        // Logging functions.
        bool write( const char* format, ... );

    private:

        FILE* file_;

    };

}

#endif // LOGGER_HPP
