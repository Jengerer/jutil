#include "avl_tree.hpp"
#include <map>
#include <windows.h>
#include <stdio.h>
#include <set>

int main( void )
{
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	// Add values.
	AVLTree<int> tree;
    QueryPerformanceCounter( &start );j
	for (int i = 0; i < 20000; ++i) {
		tree.insert( i );
	}

	// Check all values.
	for (int i = 0; i < 20000; ++i) {
		tree.remove( i );
	}
    QueryPerformanceCounter( &end );

	printf( "%d\n", end.QuadPart - start.QuadPart );

	// Try set.
	// Add values.
    QueryPerformanceCounter( &start );
	std::set<int> vals;
	for (int i = 0; i < 20000; ++i) {
		vals.insert( i );
	}
	// Check all values.
	for (int i = 0; i < 20000; ++i) {
		vals.erase( i );
	}
    QueryPerformanceCounter( &end );
	printf( "%d\n", end.QuadPart - start.QuadPart );

	system( "pause" );
	return 0;
}

