#ifndef MAP_BASE_HPP
#define MAP_BASE_HPP

#include "containers/set_base.hpp"
#include "containers/key_value_pair.hpp"

namespace JUTIL
{

	/*
	 * Map iterator class.
	 */
	template <class Key, class Value>
	class MapIterator
	{

	public:

		// Iterator constructor.
		MapIterator( void );
		MapIterator( const SetIterator< KeyValuePair<Key, Value> >& set_iterator );
		MapIterator( const MapIterator<Key, Value>& other );
		MapIterator& operator=( const MapIterator<Key, Value>& other );

		// Iteration variable getter.
		const Key& get_key( void ) const;
		const Value& get_value( void ) const;

		// Iteration continuation.
		void next( void );
		bool has_next( void ) const;

	private:

		// Iterator for base class iterator.
		SetIterator< KeyValuePair< Key, Value> > set_iterator_;

	};

	/*
	 * Map iterator default constructor.
	 */
	template <class Key, class Value>
	MapIterator<Key, Value>::MapIterator( void )
		: set_iterator_( nullptr )
	{
	}

	/*
	 * Map iterator constructor.
	 */
	template <class Key, class Value>
	MapIterator<Key, Value>::MapIterator( const SetIterator< KeyValuePair< Key, Value> >& set_iterator  )
		: set_iterator_( set_iterator )
	{
	}

	/*
	 * Set iterator copy constructor.
	 */
	template <class Key, class Value>
	MapIterator<Key, Value>::MapIterator( const MapIterator<Key, Value>& other )
		: set_iterator_( other.set_iterator_ )
	{
	}

	/*
	 * Set iterator assignment operator.
	 */
	template <class Key, class Value>
	MapIterator<Key, Value>& MapIterator<Key, Value>::operator=( const MapIterator<Key, Value>& other )
	{
		set_iterator_ = other.set_iterator_;
		return *this;
	}

	/*
	 * Get current key for iterator.
	 */
	template <class Key, class Value>
	const Key& MapIterator<Key, Value>::get_key( void ) const
	{
		return set_iterator_.get_value().get_key();
	}

	/*
	 * Get current value for iterator.
	 */
	template <class Key, class Value>
	const Value& MapIterator<Key, Value>::get_value( void ) const
	{
		return set_iterator_.get_value().get_value();
	}

	/*
	 * Move to next point in iteration.
	 */
	template <class Key, class Value>
	void MapIterator<Key, Value>::next( void )
	{
		set_iterator_.next();
	}

	/*
	 * Returns if there are more nodes to iterate through.
	 */
	template <class Key, class Value>
	bool MapIterator<Key, Value>::has_next( void ) const
	{
		return set_iterator_.has_next();
	}

}

#endif // MAP_BASE_HPP
