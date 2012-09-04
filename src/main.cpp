#include "containers/set.hpp"
#include "containers/map.hpp"
#include "containers/hash_map.hpp"
#include <map>
#include <hash_map>
#include <windows.h>
#include <stdio.h>
#include <set>

class StringHasher
{
public:
    static int hash( char* str )
    {
        return (int)*str;
    }
};

int main( void )
{
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	// Add values.
    QueryPerformanceCounter( &start );
	JUTIL::Set<int> set;
    for (int i = 0; i < 50000; i++) {
        set.insert( i );
    }
    for (int i = 0; i < 50000; i++) {
        set.remove( i );
    }
    QueryPerformanceCounter( &end );
    printf( "%u\n", end.QuadPart - start.QuadPart );

    // Add values.
    QueryPerformanceCounter( &start );
	std::set<int> set2;
    for (int i = 0; i < 50000; i++) {
        set2.insert( i );
    }
    for (int i = 0; i < 50000; i++) {
        set2.erase( i );
    }
    QueryPerformanceCounter( &end );
    printf( "%u\n", end.QuadPart - start.QuadPart );

	system( "pause" );
	return 0;
}

