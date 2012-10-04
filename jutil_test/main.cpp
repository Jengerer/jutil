#include <stdio.h>
#include <string/wide_string.hpp>
#include <string/constant_wide_string.hpp>

int main( void )
{
    JUTIL::WideString wide;
    wide.write( L"I once had %d wins, said %s.\n", 23, L"Jengerer" );
    wprintf( L"%s", wide.get_string() );
    system( "pause" );
    return 0;
}