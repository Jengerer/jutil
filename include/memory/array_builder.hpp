#ifndef ARRAY_BUILDER_HPP
#define ARRAY_BUILDER_HPP

#include "memory/base_allocator.hpp"

namespace JUTIL
{

	template <class Type>
	class ArrayBuilder
	{

	public:

		ArrayBuilder( void );
		ArrayBuilder( Type* array, size_t size );
		~ArrayBuilder( void );

		// Element functions.
		inline Type& at( size_t index );
		inline const Type& at( size_t index ) const;

		// Array buffer handles.
		void set_array( Type* array, size_t size );
		Type* get_array( void );
		const Type* get_array( void ) const;
		size_t get_size( void ) const;

		// Array buffer management.
		bool set_size( size_t size );
		Type* release( void );
		void clear( void );

	private:

		// Buffer to manage.
		Type* array_;
		size_t size_; 

	};

	/*
	 * Array builder constructor for empty array.
	 */
	template <class Type>
	ArrayBuilder<Type>::ArrayBuilder( void ) :
		array_( nullptr ),
		size_()
	{
	}

	/*
	 * Array builder constructor for existing buffer.
	 */
	template <class Type>
	ArrayBuilder<Type>::ArrayBuilder( Type* array, size_t size )
	{
		set_array( array, size );
	}

	/*
	 * Array builder destructor.
	 */
	template <class Type>
	ArrayBuilder<Type>::~ArrayBuilder( void )
	{
		clear();
	}

	/*
	 * Element getter functions.
	 */
	template <class Type>
	Type& ArrayBuilder<Type>::at( size_t index )
	{
		return array_[index];
	}

	/*
	 * Constant-reference element getter functions.
	 */
	template <class Type>
	const Type& ArrayBuilder<Type>::at( size_t index ) const
	{
		return array_[index];
	}

	/*
	 * Set buffer to be handled by the builder.
	 */
	template <class Type>
	void ArrayBuilder<Type>::set_array( Type* array, size_t size )
	{
		array_ = array;
		size_ = size;
	}

	/*
	 * Get handle to the array.
	 */
	template <class Type>
	Type* ArrayBuilder<Type>::get_array( void )
	{
		return array_;
	}

	/*
	 * Get constant handle to the array.
	 */
	template <class Type>
	const Type* ArrayBuilder<Type>::get_array( void ) const
	{
		return array_;
	}

	/*
	 * Get number of elements currently allocated.
	 */
	template <class Type>
	size_t ArrayBuilder<Type>::get_size( void ) const
	{
		return size_;
	}

	/*
	 * Attempt to set current allocation size.
	 */
	template <class Type>
	bool ArrayBuilder<Type>::set_size( size_t size )
	{
		// (Re)allocate array.
		Type* new_array = array_;
		if (size_ == 0) {
			if (!BaseAllocator::allocate_array( &new_array, size )) {
				return false;
			}
		}
		else if (!BaseAllocator::reallocate_array( &new_array, size )) {
			return false;
		}
		set_array( new_array, size );
		return true;
	}

	/*
	 * Release handle to buffer.
	 */
	template <class Type>
	Type* ArrayBuilder<Type>::release( void )
	{
		Type* temp = array_;
		set_array( nullptr, 0 );
		return temp;
	}

	/*
	 * Clear current allocation, if any.
	 */
	template <class Type>
	void ArrayBuilder<Type>::clear( void )
	{
		BaseAllocator::safe_release( &array_ );
		set_array( nullptr, 0 );
	}

}

#endif // ARRAY_BUILDER_HPP
