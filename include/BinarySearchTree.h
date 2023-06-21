// open source c library
// ==================================
//
// BinarySearchTree.h
//
// Daniel Tanase
// 14/1/22

/*
 The BinarySearchTree struct is a collection of Nodes, each containing
 pointers to no more than two children. Children with data values less than the
 parent are stored to the left (previous), and those with values grater than
 the parent are stored to the right (next).

 Since the data type of the Nodes is unknown, users must specify their own
 comparison function for the tree in its constructor. Note that these functions
 should compare the stored data - not the Nodes themselves.

 Some generic comparison functions are provided for convenience.
*/

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "node.h"

struct BinarySearchTree {
  // head points to the top-most node in the tree
  struct Node *root;

  // the "compare" function is specified by the user and is used to compare
  // the data of two nodes. It must take two void pointers as arguments and
  // return 1, -1, or 0
  int (*compare)(void *data_one, void *data_two);
  // adds a new node to the tree.  Since memory allocation is handled by the
  // node constructor, the size of this node's data must be specified
  void (*insert)(struct BinarySearchTree *self, void *data, unsigned long size);
  // finds a node in the tree, returning its data or NULL if not found
  struct Node * (*search)(struct BinarySearchTree *self, void *data);
};

// MARK: CONSTRUCTORS

// The constructor should be used to create binary search trees.
struct BinarySearchTree binary_search_tree_constructor(
  int (*compare)(void *data_one, void *data_two));
// The destructor should be used to destroy binary search trees.
void binary_search_tree_destructor(struct BinarySearchTree *binary_search_tree);

// MARK: PUBLIC HELPER FUNCTIONS

// Compare two integers and return if the first one is bigger, smaller or equal.
int compare_int(void *data_one, void *data_two);
// Compare two strings and return if the first one is greater, smaller or equal.
int compare_str(void *data_one, void *data_two);

#endif /* BinarySearchTree_h */
