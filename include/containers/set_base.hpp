#ifndef SET_BASE_HPP
#define SET_BASE_HPP

namespace JUTIL
{

	/*
	 * Set node data structure. 
	 */
	template < class Type >
	struct SetNode
	{
		// Data member.
		Type element;

		// Tree members.
		SetNode<Type>* parent;
		SetNode<Type>* left;
		SetNode<Type>* right;

		// AVL specific member.
		short height;
	};

	/*
	 * Class for iterating through a set.
	 */
	template <class Type>
	class SetIterator
	{

	public:

		// Iterator constructor.
		SetIterator( SetNode<Type>* start_node = nullptr );
		SetIterator( const SetIterator<Type>& other );
		SetIterator& operator=( const SetIterator<Type>& other );

		// Iteration variable getter.
		const Type& get_value( void ) const;

		// Iteration continuation.
		void next( void );
		bool has_next( void ) const;

	private:

		SetNode<Type>* current_;

	};

	/*
	 * Set iterator constructor.
	 */
	template <class Type>
	SetIterator<Type>::SetIterator( SetNode<Type>* start_node )
		: current_(start_node)
	{
		// Do nothing.
	}

	/*
	 * Set iterator copy constructor.
	 */
	template <class Type>
	SetIterator<Type>::SetIterator( const SetIterator<Type>& other )
		: current_( other.current_ )
	{
		// Do nothing.
	}

	/*
	 * Set iterator assignment operator.
	 */
	template <class Type>
	SetIterator<Type>& SetIterator<Type>::operator=( const SetIterator<Type>& other )
	{
		current_ = other.current_;
		return *this;
	}

	/*
	 * Set getter for current state.
	 */
	template <class Type>
	const Type& SetIterator<Type>::get_value( void ) const
	{
		return current_->element;
	}

	/*
	 * Move to next point in iteration.
	 */
	template <class Type>
	void SetIterator<Type>::next( void )
	{
		// We're only at a node if we've e
		// Move to right sub-tree if possible.
		if (current_->right != nullptr) {
			// Move to left-most node of right child.
			SetNode<Type>* node = current_->right;
			while (node->left != nullptr) {
				node = node->left;
			}
			current_ = node;
		}
		else {
			// Otherwise, move up until node isn't right child.
			SetNode<Type>* node = current_;
			while ((node->parent != nullptr) && (node == node->parent->right)) {
				node = node->parent;
			}
			current_ = node->parent;
		}
	}

	/*
	 * Returns if there are more nodes to iterate through.
	 */
	template <class Type>
	bool SetIterator<Type>::has_next( void ) const
	{
		return current_ != nullptr;
	}

}

#endif // SET_BASE_HPP
