#ifndef DATA_STRUCTURE_SHARED_HPP
#define DATA_STRUCTURE_SHARED_HPP

/*
 * Default comparator class that uses inequality operators.
 * Returns -1 if first object is greater than second.
 * Returns 0 if first is equal to second.
 * Returns 1 if first is less than second.
 */
template <class T>
class DefaultComparator<T>
{

public:

	static int compare( const T& first, const T& second );

};

/*
 * Default comparator function.
 */
template <class T>
int DefaultComparator<T>::compare( const T& first, const T& second )
{
	if (first < second) {
		return -1;
	}
	else if (first == second) {
		return 0;
	}

	return 1;
}

#endif // DATA_STRUCTURED_SHARED_HPP