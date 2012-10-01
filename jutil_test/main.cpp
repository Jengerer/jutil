#include <stdio.h>
#include <string/string_builder.hpp>
#include <string/string.hpp>
#include <string/constant_string.hpp>

int main( void )
{
    JUTIL::StringBuilder builder;
    builder.write( "I once had %i wins, said %s.\n", 23, L"Okay!" );
    JUTIL::String string( &builder );
    JUTIL::ConstantString constr = string;
    printf( "%s", constr.get_string() );
    constr.find( 'w' );
    system( "pause" );
    return 0;
}