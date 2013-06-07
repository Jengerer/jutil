#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "containers/base_container.hpp"
#include "memory/array_builder.hpp"

namespace JUTIL
{

	// Vector push expansion factors.
	const unsigned int PUSH_EXPAND_NUMERATOR   = 3;
	const unsigned int PUSH_EXPAND_DENOMINATOR = 2;

	/*
	 * Vector class that acts as a resizable array.
	 */
	template <class Type>
	class __declspec(dllexport) Vector : public BaseContainer<Type>
	{

		typedef BaseContainer<Type> BaseClass;

	public:

		Vector( void );
		~Vector( void );

		// Element management.
		inline Type& at( size_t index );
		inline const Type& at( size_t index ) const;
		bool contains( const Type& element ) const;
		bool erase( size_t index );
		bool remove( const Type& element );
		bool push( const Type& element );
		size_t index_of( const Type* element ) const;

		// Buffer management.
		bool resize( size_t length );
		bool reserve( size_t length );
		void clear( void );
		Type* get_buffer( void );
		const Type* get_buffer( void ) const;

	private:

		ArrayBuilder<Type> builder_;

	};

	/*
	 * Vector constructor.
	 */
	template <class Type>
	Vector<Type>::Vector( void )
	{
	}

	/*
	 * Vector destructor.
	 */
	template <class Type>
	Vector<Type>::~Vector( void )
	{
		clear();
	}

	/*
	 * Non-constant reference getter for index.
	 * Assumes valid index and array not nullptr.
	 */
	template <class Type>
	Type& Vector<Type>::at( size_t index )
	{
		return builder_.at( index );
	}

	/*
	 * Gets element at index (constant reference).
	 * Assumes valid index and array not nullptr.
	 */
	template <class Type>
	const Type& Vector<Type>::at( size_t index ) const
	{
		return builder_.at( index );
	}

	/*
	 * Checks whether an element exists in the array.
	 */
	template <class Type>
	bool Vector<Type>::contains( const Type& element ) const
	{
		size_t i;
		for (i = 0; i < get_length(); ++i) {
			if (at(i) == element) {
				return true;
			}
		}

		return false;
	}

	/*
	 * Remove an element from the array by index.
	 * Assumes valid index.
	 */
	template <class Type>
	bool Vector<Type>::erase( size_t i )
	{
		// Shift left
		Type* array = builder_.get_array();
		size_t length = get_length();
		memmove( array + i, array + i + 1, (length - i - 1) * sizeof(Type) );

		// TODO: If we're shrinking the array, we don't care if it fails; make set_length pass if
		// failed to realloc when shrinking.
		if (!resize( length - 1 )) {
			return false;
		}

		return true;
	}

	/*
	 * Remove an element from the array.
	 * Returns true if the element was found, false otherwise.
	 */
	template <class Type>
	bool Vector<Type>::remove( const Type& element )
	{
		// Skip empty.
		if (get_length() == 0) {
			return false;
		}

		// Find element index.
		size_t i;
		size_t length = get_length();
		for (i = 0; i < length; ++i) {
			if (at(i) == element) {
				break;
			}
		}

		// Check if found.
		if (i != length) {
			return erase( i );
		}

		return false;
	}

	/*
	 * Add an element to the end of the vector.
	 */
	template <class Type>
	bool Vector<Type>::push( const Type& element )
	{
		// Check if array needs to be expanded.
		size_t length = get_length();
		size_t buffer_size = builder_.get_size();
		if (buffer_size == length) {
			unsigned int new_buffer_size = (length + 1) * PUSH_EXPAND_NUMERATOR / PUSH_EXPAND_DENOMINATOR;
			if (!reserve( new_buffer_size )) {
				return false;
			}
		}

		// Add to end.
		at( length ) = element;
		set_length( length + 1 );
		return true;
	}

	/*
	 * Get the index of the given element.
	 * Assumes the given address is within the array boundaries.
	 */
	template <class Type>
	size_t Vector<Type>::index_of( const Type* element ) const
	{
		unsigned int base = reinterpret_cast<unsigned int>(builder_.get_array());
		unsigned int offset = reinterpret_cast<unsigned int>(element);
		unsigned int index = (offset - base) / sizeof(Type);
		return index;
	}

	/*
	 * Set new array size.
	 * Always matches buffer to length, so is destructive.
	 */
	template <class Type>
	bool Vector<Type>::resize( size_t length )
	{
		// Allocate if needed.
		if (!reserve( length )) {
			return false;
		}

		// Set base length.
		set_length( length );
		return true;
	}

	/*
	 * Reserve memory for future pushed elements.
	 */
	template <class Type>
	bool Vector<Type>::reserve( size_t length )
	{
		if (!builder_.set_size( length )) {
			return false;
		}
		return true;
	}

	/*
	 * Clear array elements.
	 */
	template <class Type>
	void Vector<Type>::clear( void )
	{
		set_length( 0 );
	}

	/*
	 * Get reference to buffer to pass as C-style array.
	 */
	template <class Type>
	Type* Vector<Type>::get_buffer( void )
	{
		return builder_.get_array();
	}

	/*
	 * Get reference to constant buffer to pass as C-style array.
	 */
	template <class Type>
	const Type* Vector<Type>::get_buffer( void ) const
	{
		return builder_.get_array();
	}

}

#endif // VECTOR_HPP
