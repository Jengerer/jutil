#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdlib.h>

/*
 * Vector class that acts as a resizable array.
 */
template <class T>
class Vector
{

public:

	Vector( void );
	~Vector( void );

	// Array retrieval.
	T& operator[]( size_t i );
	const T& operator[]( size_t i ) const;

	// Array operations/getters.
	bool has_element( const T& element ) const;
	bool remove( const T& element );
	void clear( void );
	size_t get_size( void ) const;
	bool set_size( size_t size );

private:

	T* array_;
	size_t size_;

};

/*
 * Vector constructor.
 */
template <class T>
Vector<T>::Vector( void )
{
	array_ = nullptr;
	size_ = 0;
}

/*
 * Vector destructor.
 */
template <class T>
Vector<T>::~Vector( void )
{
	clear();
}

/*
 * Non-const array operator.
 */
template <class T>
T& Vector<T>::operator[]( size_t i )
{
	return array_[i];
}

/*
 * Const array operator.
 */
template <class T>
const T& Vector<T>::operator[]( size_t i ) const
{
	return array_[i];
}

/*
 * Checks whether an element exists in the array.
 */
template <class T>
bool Vector<T>::has_element( const T& element ) const
{
	size_t i;
	for (i = 0; i < size_; ++i) {
		if (element == array_[i]) {
			return true;
		}
	}

	return false;
}

/*
 * Remove an element from the array.
 * Returns true if the element was found, false otherwise.
 */
template <class T>
bool Vector<T>::remove( const T& element )
{
	// Skip empty.
	if (size_ == 0) {
		return false;
	}

	// Find element index.
	size_t i;
	for (i = 0; i < size_; ++i) {
		if (element == array_[i]) {
			break;
		}
	}

	// Check if found.
	if (i != size_) {
		// Shift left
		memmove( array_ + i, array_ + i + 1, (size_ - i - 1) * sizeof(T) ); 
		set_size( size_ - 1 );
		return true;
	}

	return false;
}

/*
 * Clear array elements.
 */
template <class T>
void Vector<T>::clear( void )
{
	free( array_ );
}

/*
 * Get number of element cells in array.
 */
template <class T>
size_t Vector<T>::get_size( void ) const
{
	return size_;
}

/*
 * Set number of elements in array.
 * Returns true if reallocation succeeded, false otherwise.
 */
template <class T>
bool Vector<T>::set_size( size_t size )
{
	// Check if emptying.
	if (size == 0) {
		free( array_ );
		size_ = 0;
		return true;
	}

	// Attempt sizing.
	T* new_array;
	unsigned int new_size = sizeof(T) * size;
	if (size_ == 0) {
		new_array = (T*)malloc( sizeof(T) * size );
	}
	else {
		new_array = (T*)realloc( array_, new_size );
	}

	// Check successful resize.
	if (new_array == nullptr) {
		return false;
	}

	array_ = new_array;
	size_ = size;
	return true;
}

#endif // VECTOR_HPP