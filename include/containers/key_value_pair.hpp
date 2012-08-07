#ifndef KEY_VALUE_PAIR_HPP
#define KEY_VALUE_PAIR_HPP

/*
 * Key value pair object.
 */
template <class Key, class Value>
class KeyValuePair
{

public:

	KeyValuePair( const Key& key, const Value& value );

	// Resource functions.
	void operator=( const Value& value );
	const Key& get_key( void ) const;
	Value& get_value( void );
	const Value& get_value( void ) const;

private:

	Key key_;
	Value value_;

};

/*
 * Key value pair constructor.
 */
template <class Key, class Value>
KeyValuePair<Key, Value>::KeyValuePair( const Key& key, const Value& value )
{
	key_ = key;
	value_ = value;
}

/*
 * Assignment operator.
 */
template <class Key, class Value>
void KeyValuePair<Key, Value>::operator=( const Value& value )
{
	value_ = value;
}

/*
 * Constant key reference getter.
 */
template <class Key, class Value>
const Key& KeyValuePair<Key, Value>::get_key( void ) const
{
	return key_;
}

/*
 * Value reference getter.
 */
template <class Key, class Value>
Value& KeyValuePair<Key, Value>::get_value( void )
{
	return value_;
}

/*
 * Constant value reference getter.
 */
template <class Key, class Value>
const Value& KeyValuePair<Key, Value>::get_value( void ) const
{
	return value_;
}

#endif // KEY_VALUE_PAIR_HPP
