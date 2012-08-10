#include "containers/set.hpp"
#include "containers/map.hpp"
#include "containers/hash_map.hpp"
#include "memory/allocation_manager.hpp"
#include "memory/heap_allocator.hpp"
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
    JUTIL::BaseClassServices::initialize();

	LARGE_INTEGER start;
	LARGE_INTEGER end;

	// Add values.
    QueryPerformanceCounter( &start );
	JUTIL::Set<int> set;
    for (int i = 0; i < 100; i++) {
        set.insert( i );
    }
    for (int i = 0; i < 100; i++) {
        set.remove( i );
    }
    QueryPerformanceCounter( &end );
    printf( "%u\n", end.QuadPart - start.QuadPart );

	system( "pause" );
    JUTIL::AllocationManager::dump( "memory_leaks.txt" );
    JUTIL::BaseClassServices::shut_down();
	return 0;
}

