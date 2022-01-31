/*
 Note: due to the fact that several data structures (in this project) will have
 functions for "insertion", "retrieving", "removing", etc; the name of the
 functions in the implementation of the library will have the notation of "bst"
 at the end, representing -> "binary search tree".
*/

#include "BinarySearchTree.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// MARK: PUBLIC MEMBER METHODS

void insert_bst(struct BinarySearchTree *binary_search_tree,
  void *data, unsigned long size);
struct Node * search_bst(struct BinarySearchTree *binary_search_tree,
  void *data);

// MARK: PRIVATE MEMBER METHODS

struct Node * create_node_bst(void *data, unsigned long size);
void destroy_node_bst(struct Node *node);
struct Node * iterate_bst(struct BinarySearchTree *binary_search_tree,
  struct Node *cursor, void *data, int *direction);
void recursive_binary_search_tree_destructor(struct Node *node);

// The constructor takes a "compare" function pointer as its only argument and
// returns a defined BinarySearchTree struct.
struct BinarySearchTree binary_search_tree_constructor(
  int (*compare)(void *data_one, void *data_two)) {
  // create a BinarySearchTree instance to be returned
  struct BinarySearchTree binary_search_tree;

  // initialize the structure members fields
  binary_search_tree.head = NULL;

  // assigns the public member methods
  binary_search_tree.compare = compare;
  binary_search_tree.insert = insert_bst;
  binary_search_tree.search = search_bst;

  return binary_search_tree;
}

// The destructor takes a BinarySearchTree structure pointer as its only
// argument and calls the "recursive_binary_search_tree_destructor" too free
// the memory of all nodes.
void binary_search_tree_destructor(
  struct BinarySearchTree *binary_search_tree) {
  recursive_binary_search_tree_destructor(binary_search_tree->head);
}

// The "insert_bst" function adds new nodes to the binary_search_tree by
// finding their proper position.
void insert_bst(struct BinarySearchTree *binary_search_tree,
  void *data, unsigned long size) {
  // check if this is the first node in the tree
  if (!binary_search_tree->head) {
    binary_search_tree->head = create_node_bst(data, size);
  } else {
    // set the direction int pointer
    int direction = 0;
    // find the desired position
    struct Node *cursor = iterate_bst(binary_search_tree,
      binary_search_tree->head, data, &direction);

    // check if the new node should be inserted to the left or right
    if (direction == 1) {
      cursor->next = create_node_bst(data, size);
    } else if (direction == -1) {
      cursor->prev = create_node_bst(data, size);
    }
    // duplicate nodes will not be added
  }
}

// The "search_bst" function utilizes the iterate function to test if a given
// node exists in the tree. If the node is found, its data is returned.
// Otherwise, NULL is returned.
struct Node * search_bst(struct BinarySearchTree *binary_search_tree,
  void *data) {
  // set the direction int pointer
  int direction = 0;
  // utilize iterate to find the desired position
  struct Node *cursor = iterate_bst(binary_search_tree,
    binary_search_tree->head, data, &direction);

  // test if the found node is the desired node, or an adjacent one
  if (direction == 0) {
    return cursor;
  }
  return NULL;
}

// The "create_node_bst" allocates space on the heap for a node and uses the
// Node constructor to instantiate it.
struct Node * create_node_bst(void *data, unsigned long size) {
  // allocate space
  struct Node *new_node = malloc(sizeof *new_node);
  // call the constructor
  *new_node = node_constructor(data, size);

  return new_node;
}

// The "destroy_node_bst" function removes a node by deallocating it's memory
// address, this simply renames the node destructor function.
void destroy_node_bst(struct Node *node) {
  node_destructor(node);
}

// The "iterate_bst" function is a recursive algorithm that traverses the
// branches of a tree. It utilizes the compare function to determine if it
// should move left or right, and returns the cursor once there is nowhere left
// for the iterator to move. The user must take care to insrue this function
// returns the node they are actually looking for. The function takes a
// reference to the BinarySearchTree, the current position, desired data, and
// an int pointer as arguments. The int pointer becomes 1 if the desired data
// is greater than the returned node, -1 if it is less than, and 0 if they are
// equal.
struct Node * iterate_bst(struct BinarySearchTree *binary_search_tree,
  struct Node *cursor, void *data, int *direction) {
  // compare the cursor's data to the desired data
  if (binary_search_tree->compare(cursor->data, data) == 1) {
    // check if there is another node in the chain to be tested
    if (cursor->next) {
      // recursively test the next (right) node
      return iterate_bst(binary_search_tree, cursor->next, data, direction);
    } else {
      // set the direction pointer to reflect the next position is
      // desired (moving right)
      *direction = 1;
      // return the cursor
      return cursor;
    }
    // alternative outcome of the compare
  } else if (binary_search_tree->compare(cursor->data, data) == -1) {
    // check if there is another node in the chain to be tested
    if (cursor->prev) {
      // recursively test the previous (left) node
      return iterate_bst(binary_search_tree, cursor->prev, data, direction);
    } else {
      // set the direction pointer to reflect the previous position
      // is desired (moving left)
      *direction = -1;
      return cursor;
    }
    // the two data values are equal
  } else {
    // set direction
    *direction = 0;
    // return the node
    return cursor;
  }
}

// The "recursive_binary_search_tree_destructor" function will use
// "Depth First Search" algorithm to destruct the tree.
void recursive_binary_search_tree_destructor(struct Node *node) {
  // chekc the previous node
  if (node->prev) {
    recursive_binary_search_tree_destructor(node->prev);
  }
  // check the next node
  if (node->next) {
    recursive_binary_search_tree_destructor(node->next);
  }
  // destroy the node
  destroy_node_bst(node);
}

// Compare two strings and return if the first one is bigger, smaller or equal.
int binary_search_tree_str_compare(void *data_one, void *data_two) {
  int comparison = strcmp(data_one, data_two);

  // the first string is bigger
  if (comparison > 0) {
    return 1;
  }
  // the first string is smaller
  if (comparison < 0) {
    return -1;
  }
  // the strings are equal
  return 0;
}
