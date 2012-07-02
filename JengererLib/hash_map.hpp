#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include "key_value_pair.hpp"

/*
 * Hash map class for containing key-value pairs.
 */
template <class K, class V, class H>
class HashMap
{

public:

	HashMap( void );
	~HashMap( void );

	// Hash map resource functions.
	V& operator[]( const K& key );
	const V& operator[]( const Key& key ) const;
	bool has_key( const K& key ) const;

	// Iteration functions.

	// Key-value management.
	bool insert( const K& key, const V& value );
	void remove( const K& key );

private:

	Vector< KeyValuePair<K, V> > pairs_;

};

#endif // HASH_MAP_HPP