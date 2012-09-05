#include "base/logger.hpp"
#include <stdarg.h>

namespace JUTIL
{

    /*
     * Logger constructor.
     */
    Logger::Logger( void )
    {
        // Nothing.
    }

    /*
     * Logger destructor.
     */
    Logger::~Logger( void )
    {
        // Close file if open.
        if (file_ != nullptr) {
            close();
        }
    }

    /*
     * Open log to file.
     */
    bool Logger::open( const ConstantString& filename )
    {
        // Attempt to open file.
        errno_t error = fopen_s( &file_, filename.get_string(), "w" );
        if (error != 0) {
            return false;
        }

        // Create initial message.
        return write( "Logging started...\n" );
    }

    /*
     * Close file.
     */
    void Logger::close( void )
    {
        fclose( file_ );
    }

    /*
     * Write text to file.
     */
    bool Logger::write( const char* format, ... )
    {
        // Write to buffer.
        va_list args;
        va_start( args, format );
        int written = vfprintf_s( file_, format, args );
        if (written < 0) {
            return false;
        }
        va_end( args );

        // Flush buffer to file.
        return fflush( file_ ) == 0;
    }

}