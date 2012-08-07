#ifndef CONTAINER_COMMON_H
#define CONTAINER_COMMON_H

/*
 * Default comparator for container objects.
 */
template < class Type >
class DefaultComparator
{

public:

	// Do generic operator comparison.
	static int compare( const Type& a, const Type& b )
	{
        if (a < b) {
            return -1;
        }
        else if (a > b) {
            return 1;
        }
        return 0;
	}

};

#endif // CONTAINER_COMMON_H
