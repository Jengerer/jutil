#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include "key_value_pair.hpp"

/*
 * Hash map class for containing key-value pairs.
 */
template <class Hash, class Key, class Value, class Hasher>
class HashMap
{

public:

	HashMap( void );
	~HashMap( void );

	// Hash map resource functions.
	Value& operator[]( const Key& key );
	const Value& operator[]( const Key& key ) const;
	bool has_key( const Key& key ) const;

	// Iteration functions.

	// Key-value management.
	bool insert( const Key& key, const Value& value );
	void remove( const Key& key );

private:

	Vector< KeyValuePair<K, V> > pairs_;

};

#endif // HASH_MAP_HPP