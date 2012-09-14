#ifndef STRING_BUILDER_HPP
#define STRING_BUILDER_HPP

#include "string/base_string_builder.hpp"

namespace JUTIL
{

    /*
     * Class for handling a C-style string buffer.
     */
    class __declspec(dllexport) StringBuilder : public BaseStringBuilder<char>
    {

    public:

        StringBuilder( void );
        ~StringBuilder( void );

        // Buffer managing functions.
        const char* write( const char* format, ... );
        const char* write( const char* format, va_list args );

    private:

        // Base class typedef for inner functions.
        typedef BaseStringBuilder<char> BaseClass;

    };

}

#endif // STRING_BUILDER_HPP
