#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <stdlib.h>
#include "container_common.h"


// Balance constants.
const int BALANCE_TWO_LEFT	= -2;
const int BALANCE_ONE_LEFT	= -1;
const int BALANCE_EVEN		= 0;
const int BALANCE_ONE_RIGHT	= 1;
const int BALANCE_TWO_RIGHT = 2;


/*
 * Generic AVL node struct.
 */
template < class Type >
struct AVLNode
{
	// Data member.
	Type element;

	// Tree members.
	AVLNode<Type>* parent;
	AVLNode<Type>* left;
	AVLNode<Type>* right;

	// AVL specific member.
	short height;
};


/*
 * AVL tree data structure class.
 */
template < class Type, class Comparator = DefaultComparator<Type> >
class AVLTree
{

public:

	AVLTree( void );
	~AVLTree( void );

	// Binary tree operations.
	bool insert( const Type& element );
	void remove( const Type& element );
	bool contains( const Type& element ) const;
	void clear( void );

private:

	// Node getting.
	AVLNode<Type>* find_node( const Type& element ) const;
	static AVLNode<Type>* get_minimum( AVLNode<Type>* node );
	static AVLNode<Type>* get_maximum( AVLNode<Type>* node );

	// Node balancing.
	static int get_height( AVLNode<Type>* node );
	static bool update_height( AVLNode<Type>* node );
	static int get_balance_factor( AVLNode<Type>* node );
	void rotate_left( AVLNode<Type>** root_link );
	void rotate_right( AVLNode<Type>** root_link );

	// Node link handling.
	AVLNode<Type>** get_node_link( AVLNode<Type>* node );
	static AVLNode<Type>* create_node( const Type& element );
	static void set_left( AVLNode<Type>* parent, AVLNode<Type>* child );
	static void set_right( AVLNode<Type>* parent, AVLNode<Type>* child );

	// Tree balancing functions.
	void balance_tree( AVLNode<Type>* node );
	bool balance_node( AVLNode<Type>* node );

private:

	AVLNode<Type>* root_;

};


/*
 * AVL tree constructor.
 */
template <class Type, class Comparator>
AVLTree<Type, Comparator>::AVLTree( void )
{
	root_ = nullptr;
}


/*
 * AVL tree destructor.
 */
template <class Type, class Comparator>
AVLTree<Type, Comparator>::~AVLTree( void )
{
	clear();
}


/*
 * Insert an element into the tree.
 */
template <class Type, class Comparator>
bool AVLTree<Type, Comparator>::insert( const Type& element )
{
	// Create node.
	AVLNode<Type>* node = create_node( element );
	if (node == nullptr) {
		return false;
	}

	// Do regular tree insertion.
	if (root_ == nullptr) {
		root_ = node;
	}
	else {
		AVLNode<Type>* current = root_;

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

	return true;
}


/*
 * Remove an element from the tree.
 */
template <class Type, class Comparator>
void AVLTree<Type, Comparator>::remove( const Type& element )
{
	// Find the node.
	AVLNode<Type>* node = find_node( element );
	if (node == nullptr) {
		return;
	}

	// If we have both children, get successor.
	AVLNode<Type>* replacement = nullptr;
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
	free( node );
}


/*
 * Check if a node exists in the tree.
 */
template <class Type, class Comparator>
bool AVLTree<Type, Comparator>::contains( const Type& element ) const
{
	return find_node( element ) != nullptr;
}


/*
 * Clear all elements from the tree.
 */
template <class Type, class Comparator>
void AVLTree<Type, Comparator>::clear( void )
{
	// Not implemented yet. Just keep removing root?
}


/*
 * Find a node by its element.
 */
template <class Type, class Comparator>
AVLNode<Type>* AVLTree<Type, Comparator>::find_node( const Type& element ) const
{
	// Start at root.
	AVLNode<Type>* node = root_;
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
AVLNode<Type>* AVLTree<Type, Comparator>::get_minimum( AVLNode<Type>* node )
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
AVLNode<Type>* AVLTree<Type, Comparator>::get_maximum( AVLNode<Type>* node )
{
	// Keep going right!
	while (node->right != nullptr) {
		node = node->right;
	}

	return node;
}


/*
 * Create an AVL node.
 */
template <class Type, class Comparator>
AVLNode<Type>* AVLTree<Type, Comparator>::create_node( const Type& element )
{
	// Allocate node.
	AVLNode<Type>* node = (AVLNode<Type>*)malloc( sizeof(AVLNode<Type>) );
	if (node == nullptr) {
		return nullptr;
	}

	// Instantiate node.
	node->element = element;
	node->parent = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;
	return node;
};


/*
 * Set a node's left child and update its parent.
 */
template <class Type, class Comparator>
void AVLTree<Type, Comparator>::set_left( AVLNode<Type>* parent, AVLNode<Type>* child )
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
void AVLTree<Type, Comparator>::set_right( AVLNode<Type>* parent, AVLNode<Type>* child )
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
int AVLTree<Type, Comparator>::get_height( AVLNode<Type>* node )
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
bool AVLTree<Type, Comparator>::update_height( AVLNode<Type>* node )
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
int AVLTree<Type, Comparator>::get_balance_factor( AVLNode<Type>* node )
{
	return get_height( node->right ) - get_height( node->left );
}


/*
 * Get highest pointer reference to a node in the tree.
 */
template <class Type, class Comparator>
AVLNode<Type>** AVLTree<Type, Comparator>::get_node_link( AVLNode<Type>* node )
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
void AVLTree<Type, Comparator>::rotate_left( AVLNode<Type>** root_link )
{
	// Track two main elements.
	AVLNode<Type>* original = *root_link;
	AVLNode<Type>* new_root = original->right;

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
void AVLTree<Type, Comparator>::rotate_right( AVLNode<Type>** root_link )
{
	// Track two main elements.
	AVLNode<Type>* original = *root_link;
	AVLNode<Type>* new_root = original->right;

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
void AVLTree<Type, Comparator>::balance_tree( AVLNode<Type>* node )
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
bool AVLTree<Type, Comparator>::balance_node( AVLNode<Type>* node )
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

#endif // AVL_TREE_HPP