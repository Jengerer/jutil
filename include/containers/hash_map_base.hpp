#ifndef HASH_MAP_BASE_HPP
#define HASH_MAP_BASE_HPP

namespace JUTIL
{

    /*
     * Hash map iterator class.
     */
    template <class Hash, class Value>
    class HashMapIterator
    {

    public:

        // Iterator constructor.
        HashMapIterator( void );
        HashMapIterator( const MapIterator<Hash, Value>& map_iterator );
        HashMapIterator( const HashMapIterator<Hash, Value>& other );
        HashMapIterator& operator=( const HashMapIterator<Hash, Value>& other );

        // Iteration variable getter.
        const Value& get_value( void ) const;

        // Iteration continuation.
        void next( void );
        bool has_next( void ) const;

    private:

        // Iterator for base class iterator.
        MapIterator<Hash, Value> map_iterator_;

    };

    /*
     * Map iterator default constructor.
     */
    template <class Hash, class Value>
    HashMapIterator<Hash, Value>::HashMapIterator( void )
        : map_iterator_( nullptr )
    {
        // Do nothing.
    }

    /*
     * Map iterator constructor.
     */
    template <class Hash, class Value>
    HashMapIterator<Hash, Value>::HashMapIterator( const MapIterator<Hash, Value>& map_iterator  )
        : map_iterator_( map_iterator )
    {
        // Do nothing.
    }

    /*
     * Set iterator copy constructor.
     */
    template <class Hash, class Value>
    HashMapIterator<Hash, Value>::HashMapIterator( const HashMapIterator<Hash, Value>& other )
        : map_iterator_( other.map_iterator_ )
    {
        // Do nothing.
    }

    /*
     * Set iterator assignment operator.
     */
    template <class Hash, class Value>
    HashMapIterator<Hash, Value>& HashMapIterator<Hash, Value>::operator=( const HashMapIterator<Hash, Value>& other )
    {
        map_iterator_ = other.map_iterator_;
        return *this;
    }

    /*
     * Get current value for iterator.
     */
    template <class Hash, class Value>
    const Value& HashMapIterator<Hash, Value>::get_value( void ) const
    {
        return map_iterator_.get_value();
    }

    /*
     * Move to next point in iteration.
     */
    template <class Hash, class Value>
    void HashMapIterator<Hash, Value>::next( void )
    {
        map_iterator_.next();
    }

    /*
     * Returns if there are more nodes to iterate through.
     */
    template <class Hash, class Value>
    bool HashMapIterator<Hash, Value>::has_next( void ) const
    {
        return map_iterator_.has_next();
    }

}

#endif // HASH_MAP_BASE_HPP
