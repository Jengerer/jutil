#include "containers/avl_tree.hpp"
#include "containers/map.hpp"
#include <map>
#include <hash_map>
#include <windows.h>
#include <stdio.h>
#include <set>

int main( void )
{
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	// Add values.
    QueryPerformanceCounter( &start );
	JUTIL::Map<int, int> map;
    for (int i = 0; i < 100000; i++) {
        map.insert( i, i+1 );
    }
    for (int i = 0; i < 100000; i++) {
        map.remove( i );
    }
    QueryPerformanceCounter( &end );
    printf( "%u\n", end.QuadPart - start.QuadPart );
    
    // Add values.
    QueryPerformanceCounter( &start );
	std::map<int, int> stl;
    for (int i = 0; i < 100000; i++) {
        stl[i] = i+1;
    }
    for (int i = 0; i < 100000; i++) {
        stl.erase( i );
    }
    QueryPerformanceCounter( &end );
    printf( "%u\n", end.QuadPart - start.QuadPart );
    

	system( "pause" );
	return 0;
}

