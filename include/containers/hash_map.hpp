#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include "map.hpp"

namespace JUTIL
{

    /*
     * Hash map class for containing key-value pairs.
     *
     * Template argument `Hasher` is a class with a
     * static function `Hash hash( Key )`.
     *
     * Template argument `HashComparator` is a class 
     * with a static function `int compare( Hash, Hash )`.
     */
    template <
        class Hash,
        class Key,
        class Value,
        class Hasher,
        class HashComparator = DefaultComparator<Hash> >
    class HashMap
    {

    public:

	    HashMap( void );
	    ~HashMap( void );

	    // Hash map resource functions.
	    bool contains( const Key& key ) const;
        bool get( const Key& key, Value* out ) const;

	    // Key-value management.
	    bool insert( const Key& key, const Value& value );
	    void remove( const Key& key );

    private:

        Map<Hash, Value, HashComparator> map_;

    };


    /*
     * Hash map constructor.
     */
    template <class Hash, class Key, class Value, class Hasher, class HashComparator>
    HashMap<Hash, Key, Value, Hasher, HashComparator>::HashMap( void )
    {
        // Nothing.
    }


    /*
     * Hash map destructor.
     */
    template <class Hash, class Key, class Value, class Hasher, class HashComparator>
    HashMap<Hash, Key, Value, Hasher, HashComparator>::~HashMap( void )
    {
        map_.clear();
    }


    /*
     * Check for key in hash map.
     */
    template <class Hash, class Key, class Value, class Hasher, class HashComparator>
    bool HashMap<Hash, Key, Value, Hasher, HashComparator>::contains( const Key& key ) const
    {
        // Check for hash.
        Hash hash = Hasher::hash( key );  
        return map_.contains( hash );
    }


    /*
     * Get value for key from hash map.
     */
    template <class Hash, class Key, class Value, class Hasher, class HashComparator>
    bool HashMap<Hash, Key, Value, Hasher, HashComparator>::get( const Key& key, Value* out ) const
    {
        // Get value for hash.
        Hash hash = Hasher::hash( key );
        return map_.get( hash, out );
    }


    /*
     * Insert key-value into map.
     */
    template <class Hash, class Key, class Value, class Hasher, class HashComparator>
    bool HashMap<Hash, Key, Value, Hasher, HashComparator>::insert( const Key& key, const Value& value )
    {
        // Insert key-value into map.
        Hash hash = Hasher::hash( key );
        return map_.insert( hash, value );
    }


    /*
     * Remove pair from map by key.
     */
    template <class Hash, class Key, class Value, class Hasher, class HashComparator>
    void HashMap<Hash, Key, Value, Hasher, HashComparator>::remove( const Key& key )
    {
        // Remove from map by hash.
        Hash hash = Hasher::hash( key );
        map_.remove( hash );
    }

}

#endif // HASH_MAP_HPP