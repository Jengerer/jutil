#include <stdio.h>
#include <string/string.hpp>

int main( void )
{
    JUTIL::ConstantString a( "I am person a person" );
    JUTIL::ConstantString sub( "person" );
	printf( "person found at %d\n", a.find( &sub ) );
    system( "pause" );
    return 0;
}