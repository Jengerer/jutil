#ifndef KEY_VALUE_PAIR_HPP
#define KEY_VALUE_PAIR_HPP

/*
 * Key value pair object.
 */
template <class K, class V>
class KeyValuePair
{

public:

	KeyValuePair( K& key, V& value );

	// Resource functions.
	void operator=( const V& value );
	const K& get_key( void ) const;
	V& get_value( void );
	const V& get_value( void ) const;

private:

	K key_;
	V value_;

};

/*
 * Key value pair constructor.
 */
KeyValuePair::KeyValuePair( K& key, V& value )
{
	key_ = key;
	value_ = value;
}

/*
 * Assignment operator.
 */
void KeyValuePair::operator=( const V& value )
{
	value_ = value;
}

/*
 * Constant key reference getter.
 */
const K& KeyValuePair::get_key( void ) const
{
	return key_;
}

/*
 * Value reference getter.
 */
V& KeyValuePair::get_value( void )
{
	return value_;
}

/*
 * Constant value reference getter.
 */
const V& KeyValuePair::get_value( void ) const
{
	return value_;
}

#endif // KEY_VALUE_PAIR_HPP