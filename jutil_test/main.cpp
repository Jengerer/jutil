#include <stdio.h>
#include <string/string_builder.hpp>
#include <string/wide_string_builder.hpp>
#include <string/wide_string.hpp>
#include <string/constant_wide_string.hpp>

int main( void )
{
    JUTIL::WideStringBuilder builder;
    builder.write( L"I once had %i wins, said %s.\n", 23, L"Okay!" );
    JUTIL::WideString string( &builder );
    JUTIL::ConstantWideString constr = string;
    wprintf( L"%s", constr.get_string() );
    system( "pause" );
    return 0;
}