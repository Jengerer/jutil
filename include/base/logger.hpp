#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "string_builder.hpp"

namespace JUTIL
{

    class Logger
    {

    public:

        Logger( void );
        ~Logger( void );

        // File handling.
        bool open( const char* filename );
        void close( void );

        // Logging functions.
        

    };

}

#endif // LOGGER_HPP
