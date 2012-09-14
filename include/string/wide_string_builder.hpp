#ifndef WIDE_STRING_BUILDER_HPP
#define WIDE_STRING_BUILDER_HPP

#include "string/base_string_builder.hpp"

namespace JUTIL
{

    /*
     * Class for handling a wide C-style string buffer.
     */
    class __declspec(dllexport) WideStringBuilder : public BaseStringBuilder<wchar_t>
    {

    public:

        WideStringBuilder( void );
        ~WideStringBuilder( void );

        // Buffer managing functions.
        const wchar_t* write( const wchar_t* format, ... );
        const wchar_t* write( const wchar_t* format, va_list args );

    private:

        // Base class typedef for inner functions.
        typedef BaseStringBuilder<wchar_t> BaseClass;

    };

}

#endif // WIDE_STRING_BUILDER_HPP
