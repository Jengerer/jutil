#ifndef SET_HPP
#define SET_HPP

#include "containers/base_container.hpp"
#include "containers/container_common.hpp"
#include "containers/set_base.hpp"
#include "memory/base_allocator.hpp"

namespace JUTIL
{

	// Balance constants.
	const int BALANCE_TWO_LEFT  = -2;
	const int BALANCE_ONE_LEFT  = -1;
	const int BALANCE_EVEN      = 0;
	const int BALANCE_ONE_RIGHT = 1;
	const int BALANCE_TWO_RIGHT = 2;

	/*
	 * Set implementation of set.
	 */
	template < class Type, class Comparator = DefaultComparator<Type> >
	class Set : public BaseContainer<Type>
	{

	public:

		typedef SetIterator<Type> Iterator;

	public:

		Set( void );
		virtual ~Set( void );

		// Set operations.
		bool insert( const Type& element );
		void remove( const Type& element );
		bool contains( const Type& element ) const;
		void clear( void );

		// Iteration functions.
		Iterator begin( void ) const;

	private:

		// Node getting.
		SetNode<Type>* find_node( const Type& element ) const;
		static SetNode<Type>* get_minimum( SetNode<Type>* node );
		static SetNode<Type>* get_maximum( SetNode<Type>* node );

		// Node balancing.
		static int get_height( SetNode<Type>* node );
		static bool update_height( SetNode<Type>* node );
		static int get_balance_factor( SetNode<Type>* node );
		void rotate_left( SetNode<Type>** root_link );
		void rotate_right( SetNode<Type>** root_link );

		// Node link handling.
		SetNode<Type>** get_node_link( SetNode<Type>* node );
		SetNode<Type>* create_node( const Type& element );
		static void set_left( SetNode<Type>* parent, SetNode<Type>* child );
		static void set_right( SetNode<Type>* parent, SetNode<Type>* child );

		// Tree balancing functions.
		void balance_tree( SetNode<Type>* node );
		bool balance_node( SetNode<Type>* node );

	protected:

		SetNode<Type>* root_;

	};


	/*
	 * Set constructor.
	 */
	template <class Type, class Comparator>
	Set<Type, Comparator>::Set( void ) :
		root_( nullptr )
	{
	}

	/*
	 * Set destructor.
	 */
	template <class Type, class Comparator>
	Set<Type, Comparator>::~Set( void )
	{
		clear();
	}

	/*
	 * Insert an element into the tree.
	 * Assumes element does NOT already exist in tree.
	 */
	template <class Type, class Comparator>
	bool Set<Type, Comparator>::insert( const Type& element )
	{
		// Create node.
		SetNode<Type>* node = create_node( element );
		if (node == nullptr) {
			return false;
		}

		// Do regular tree insertion.
		if (root_ == nullptr) {
			root_ = node;
		}
		else {
			SetNode<Type>* current = root_;

			// Loop until we've been inserted.
			while (current != node) {
				// Check where it fits.
				int compare = Comparator::compare( element, current->element );
				if (compare == -1) {
					if (current->left == nullptr) {
						set_left( current, node );
					}
					current = current->left;
				}
				else {
					if (current->right == nullptr) {
						set_right( current, node );
					}
					current = current->right;
				}
			}

			// Now balance the tree starting from parent.
			balance_tree( current->parent );
		}

		size_t length = get_length();
		set_length( length + 1 );
		return true;
	}

	/*
	 * Remove an element from the tree.
	 */
	template <class Type, class Comparator>
	void Set<Type, Comparator>::remove( const Type& element )
	{
		// Find the node.
		SetNode<Type>* node = find_node( element );
		if (node == nullptr) {
			return;
		}

		// If we have both children, get successor.
		SetNode<Type>* replacement = nullptr;
		if (node->left != nullptr && node->right != nullptr) {
			// Try take in-order predecessor.
			replacement = get_minimum( node->right );

			// Move their element here and now replace them.
			node->element = replacement->element;
			node = replacement;
			replacement = nullptr;
		}

		// If only left child, move them here.
		if (node->left != nullptr) {
			replacement = node->left;
		}
		else if (node->right != nullptr) {
			// Only right child, move them here.
			replacement = node->right;
		}

		// Enact replacment.
		*get_node_link( node ) = replacement;
		if (replacement != nullptr) {
			replacement->parent = node->parent;
		}

		// Balance the tree.
		balance_tree( node->parent );

		// Delete node.
		JUTIL::BaseAllocator::release( node );
		size_t length = get_length();
		set_length( length - 1 );
	}

	/*
	 * Check if a node exists in the tree.
	 */
	template <class Type, class Comparator>
	bool Set<Type, Comparator>::contains( const Type& element ) const
	{
		return find_node( element ) != nullptr;
	}

	/*
	 * Clear all elements from the tree.
	 */
	template <class Type, class Comparator>
	void Set<Type, Comparator>::clear( void )
	{
		// Can probably optimize this.
		// Put tree into a straight line.
		SetNode<Type>* node = root_;
		while (node != nullptr) {
			// Rotate right until no left.
			while (node->left != nullptr) {
				rotate_right( get_node_link( node ) );

				// Move back up (root node just got moved to right).
				node = node->parent;
			}

			// Move to next child.
			node = node->right;
		}

		// Now just remove all.
		node = root_;
		while (node != nullptr) {
			SetNode<Type>* temp = node->right;
			JUTIL::BaseAllocator::release( node );
			node = temp;
		}

		// No root.
		root_ = nullptr;
		set_length( 0 );
	}

	/*
	 * Return iterator for beginning element.
	 */
	template <class Type, class Comparator>
	SetIterator<Type> Set<Type, Comparator>::begin( void ) const
	{
		// Get left-most of root.
		SetNode<Type>* start = root_;
		if (start != nullptr) {
			while (start->left != nullptr) {
				start = start->left;
			}
		}
		return Iterator(start);
	}

	/*
	 * Find a node by its element.
	 */
	template <class Type, class Comparator>
	SetNode<Type>* Set<Type, Comparator>::find_node( const Type& element ) const
	{
		// Start at root.
		SetNode<Type>* node = root_;
		while (node != nullptr) {
			int compare = Comparator::compare( element, node->element );
			if (compare == 0) {
				return node;
			}
			else if (compare == -1) {
				node = node->left;
			}
			else {
				node = node->right;
			}
		}

		// Not found.
		return nullptr;
	}

	/*
	 * Get left-most subchild from a starting node.
	 */
	template <class Type, class Comparator>
	SetNode<Type>* Set<Type, Comparator>::get_minimum( SetNode<Type>* node )
	{
		// Keep going left!
		while (node->left != nullptr) {
			node = node->left;
		}

		return node;
	}


	/*
	 * Get right-most subchild from starting node.
	 */
	template <class Type, class Comparator>
	SetNode<Type>* Set<Type, Comparator>::get_maximum( SetNode<Type>* node )
	{
		// Keep going right!
		while (node->right != nullptr) {
			node = node->right;
		}

		return node;
	}

	/*
	 * Create an set node.
	 */
	template <class Type, class Comparator>
	SetNode<Type>* Set<Type, Comparator>::create_node( const Type& element )
	{
		// Allocate node.
		SetNode<Type>* node = nullptr;
		if (!BaseAllocator::allocate( &node )) {
			return nullptr;
		}

		// Instantiate node.
		node->element = element;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->height = 1;
		return node;
	}

	/*
	 * Set a node's left child and update its parent.
	 */
	template <class Type, class Comparator>
	void Set<Type, Comparator>::set_left( SetNode<Type>* parent, SetNode<Type>* child )
	{
		// Update dependencies.
		parent->left = child;
		if (child != nullptr) {
			child->parent = parent;
		}
	}

	/*
	 * Set a node's right child and update its parent.
	 */
	template <class Type, class Comparator>
	void Set<Type, Comparator>::set_right( SetNode<Type>* parent, SetNode<Type>* child )
	{
		// Update dependencies.
		parent->right = child;
		if (child != nullptr) {
			child->parent = parent;
		}
	}

	/*
	 * Get node height.
	 */
	template <class Type, class Comparator>
	int Set<Type, Comparator>::get_height( SetNode<Type>* node )
	{
		// Node exists?
		if (node == nullptr) {
			return 0;
		}

		return node->height;
	}

	/*
	 * Update height of node and return whether it changed.
	 */
	template <class Type, class Comparator>
	bool Set<Type, Comparator>::update_height( SetNode<Type>* node )
	{
		// Get height of children.
		int old_height = node->height;
		int left = get_height( node->left );
		int right = get_height( node->right );

		// Set as maximum plus one.
		node->height = (left > right ? left : right) + 1;
		return (old_height != node->height);
	}

	/*
	 * Get node balance factor.
	 */
	template <class Type, class Comparator>
	int Set<Type, Comparator>::get_balance_factor( SetNode<Type>* node )
	{
		return get_height( node->right ) - get_height( node->left );
	}

	/*
	 * Get highest pointer reference to a node in the tree.
	 */
	template <class Type, class Comparator>
	SetNode<Type>** Set<Type, Comparator>::get_node_link( SetNode<Type>* node )
	{
		// Highest reference is root if no parent.
		if (node->parent == nullptr) {
			return &root_;
		}
		else if (node == node->parent->left) {
			return &node->parent->left;
		}
		else {
			return &node->parent->right;
		}
	}

	/*
	 * Rotate a node left starting with its highest reference link.
	 * Node must at least have a right child on call.
	 */
	template <class Type, class Comparator>
	void Set<Type, Comparator>::rotate_left( SetNode<Type>** root_link )
	{
		// Track two main elements.
		SetNode<Type>* original = *root_link;
		SetNode<Type>* new_root = original->right;

		// Update parent of new root.
		new_root->parent = original->parent;
		*root_link = new_root;

		// Shift them.
		set_right( original, new_root->left );
		set_left( new_root, original );

		// Update heights.
		update_height( original );
		update_height( new_root );
	}

	/*
	 * Rotate a node right starting with its highest reference link.
	 * Node must at least have a left child on call.
	 */
	template <class Type, class Comparator>
	void Set<Type, Comparator>::rotate_right( SetNode<Type>** root_link )
	{
		// Track two main elements.
		SetNode<Type>* original = *root_link;
		SetNode<Type>* new_root = original->left;

		// Update link of new root.
		new_root->parent = original->parent;
		*root_link = new_root;

		// Shift them.
		set_left( original, new_root->right );
		set_right( new_root, original );

		// Update heights.
		update_height( original );
		update_height( new_root );
	}

	/*
	 * Balance a tree starting at a node.
	 */
	template <class Type, class Comparator>
	void Set<Type, Comparator>::balance_tree( SetNode<Type>* node )
	{
		// Keep going until balancing doesn't need to happen.
		while (node != nullptr) {
			if (balance_node( node )) {
				// Node was rotated, go to its original parent.
				node = node->parent->parent;
			}
			else if (!update_height( node )) {
				// No balancing, no height updating, we're done.
				break;
			}
			else {
				node = node->parent;
			}
		}
	}

	/*
	 * Balance a node.
	 */
	template <class Type, class Comparator>
	bool Set<Type, Comparator>::balance_node( SetNode<Type>* node )
	{
		// Get balance factor.
		int balance = get_balance_factor( node );
		if (balance == BALANCE_TWO_RIGHT) {
			// Is it a right-left case?
			int right_balance = get_balance_factor( node->right );
			if (right_balance == BALANCE_ONE_LEFT) {
				rotate_right( &node->right );
			}
			rotate_left( get_node_link( node ) );
			return true;
		}
		else if (balance == BALANCE_TWO_LEFT) {
			// Is it a left-right case?
			int left_balance = get_balance_factor( node->left );
			if (left_balance == BALANCE_ONE_RIGHT) {
				rotate_left( &node->left );
			}
			rotate_right( get_node_link( node ) );
			return true;
		}

		// No balancing done.
		return false;
	}

}

#endif // SET_HPP
