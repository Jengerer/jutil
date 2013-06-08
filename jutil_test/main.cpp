#include <stdio.h>
#include <string/string.hpp>

int main( void )
{
	JUTIL::DynamicString strang;
	strang.write("Do %s.\n", "it");
	printf(strang.get_string());

	JUTIL::DynamicWideString string;
	string.write(L"Do %s.\n", L"it");
	wprintf(string.get_string());
	system( "pause" );
	return 0;
}