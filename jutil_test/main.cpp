#include <stdio.h>
#include <containers/vector.hpp>

int main( void )
{
	JUTIL::Vector<int> vector;
	if (!vector.reserve(20)) {
		return -1;
	}

	for (unsigned int i = 0; i < 20; ++i) {
		vector.push( i );
	}
	system( "pause" );
	return 0;
}