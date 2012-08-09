#ifndef MAP_HPP
#define MAP_HPP

#include "containers/set.hpp"
#include "containers/key_value_pair.hpp"

namespace JUTIL
{

    /*
     * Set of key-value pairs.
     */
    template < class Key, class Value, class KeyComparator = DefaultComparator<Key> >
    class Map : public Set< 
        KeyValuePair< Key, Value >,
        KeyValueComparator< Key, Value, KeyComparator > >
    {
    
    typedef Set< 
        KeyValuePair< Key, Value >,
        KeyValueComparator< Key, Value, KeyComparator > > BaseClass;

    public:

        Map( void );
        ~Map( void );        

        // Map functions.
        bool insert( const Key& key, const Value& value );
        void remove( const Key& key );
        bool contains( const Key& key ) const;
        bool get( const Key& key, Value* out ) const;

    private:

        // Find node by key.
        KeyValuePair<Key, Value>* find_pair( const Key& key ) const;

    };


    /*
     * AVL tree map constructor.
     */
    template <class Key, class Value, class KeyComparator>
    Map<Key, Value, KeyComparator>::Map( void )
    {
        // Do nothing.
    }


    /*
     * AVL tree map destructor.
     */
    template <class Key, class Value, class KeyComparator>
    Map<Key, Value, KeyComparator>::~Map( void )
    {
        // Do nothing.
    }


    /*
     * Insert into AVL tree map by key/value.
     */
    template <class Key, class Value, class KeyComparator>
    bool Map<Key, Value, KeyComparator>::insert( const Key& key, const Value& value )
    {
        // Insert key-value pair.
        KeyValuePair<Key, Value> pair( key, value );
        return BaseClass::insert( pair );
    }


    /*
     * Removes key-value pair from map.
     */
    template <class Key, class Value, class KeyComparator>
    void Map<Key, Value, KeyComparator>::remove( const Key& key )
    { 
        // Remove key-value pair.
        KeyValuePair<Key, Value>* pair = find_pair( key );
        if (pair == nullptr) {
            return;
        }

        // Remove pair.
        BaseClass::remove( *pair ); 
    }


    /*
     * Checks if key exists in map.
     */
    template <class Key, class Value, class KeyComparator>
    bool Map<Key, Value, KeyComparator>::contains( const Key& key ) const
    { 
        return find_pair( key ) != nullptr;
    }


    /*
     * Get value for key, if exists.
     */
    template <class Key, class Value, class KeyComparator>
    bool Map<Key, Value, KeyComparator>::get( const Key& key, Value* out ) const
    { 
        // Get pair for key.
        KeyValuePair<Key, Value>* pair = find_pair( key );
        if (pair != nullptr) {
            *out = pair->get_value();
            return true;
        }

        return false; 
    }


    /*
     * Find pair by key.
     */
    template <class Key, class Value, class KeyComparator>
    KeyValuePair<Key, Value>* Map<Key, Value, KeyComparator>::find_pair( const Key& key ) const
    {
        // Start at root.
        SetNode< KeyValuePair<Key, Value> >* node = root_;
        while (node != nullptr) {
            int compare = KeyComparator::compare( key, node->element.get_key() );
            if (compare == 0) {
                return &node->element;
            }
            else if (compare == -1) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        // Not found by key.
        return nullptr;
    }

}

#endif // AVL_TREE_MAP_HPP
