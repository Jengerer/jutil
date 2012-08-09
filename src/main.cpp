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
	JUTIL::HeapAllocator allocator;
    JUTIL::Set<int>* set = new (&allocator) JUTIL::Set<int>();
    JUTIL::AllocationManager::dump( "memory_leaks.txt" );
	/*LARGE_INTEGER start;
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
    printf( "%u\n", end.QuadPart - start.QuadPart );*/    

	system( "pause" );
	return 0;
}

