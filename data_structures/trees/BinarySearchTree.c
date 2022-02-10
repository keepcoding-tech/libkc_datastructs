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

void insert_bst(struct BinarySearchTree *self, void *data, unsigned long size);
struct Node * search_bst(struct BinarySearchTree *self, void *data);

// MARK: PRIVATE MEMBER METHODS

struct Node * create_node_bst(void *data, unsigned long size);
void destroy_node_bst(struct Node *node_to_destroy);
void recursive_binary_search_tree_destructor(struct Node *node);

// The constructor takes a "compare" function pointer as its only argument and
// returns a defined BinarySearchTree struct.
struct BinarySearchTree binary_search_tree_constructor(
  int (*compare)(void *data_one, void *data_two)) {
  // create a BinarySearchTree instance to be returned
  struct BinarySearchTree binary_search_tree;

  // initialize the structure members fields
  binary_search_tree.root = NULL;

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
  recursive_binary_search_tree_destructor(binary_search_tree->root);
}

// To insert a new node into the tree, we need to mantain the order property.
struct Node * insert_node_bst(struct BinarySearchTree *tree,
  struct Node *node, void *data, unsigned long size) {
  // check if this is the first node in the tree
  if (!node) {
    node = create_node_bst(data, size);
    // check if the current node's data is smaller (move to left)
  } else if (tree->compare(data, node->data) == -1) {
    node->prev = insert_node_bst(tree, node->prev, data, size);
    // check if the current node's data is greater (move to right)
  } else if (tree->compare(data, node->data) == 1) {
    node->next = insert_node_bst(tree, node->next, data, size);
  }

  return node;
}

// The "insert_bst" function adds new nodes to the tree
void insert_bst(struct BinarySearchTree *self, void *data, unsigned long size) {
  self->root = insert_node_bst(self, self->root, data, size);
}

// The "search_bst" function utilizes the iterate function to test if a given
// node exists in the tree. If the node is found, its data is returned.
// Otherwise, NULL is returned.
struct Node * search_bst(struct BinarySearchTree *self, void *data) {
  // start searching from the root of the tree
  struct Node *current = self->root;

  while (current) {
    // check if the desired node was found and return it
    if (self->compare(current->data, data) == 0) {
      return current;
      // check if the current node's data is smaller (move to right)
    } else if (self->compare(current->data, data) == -1) {
      current = current->next;
      // check if the current node's data is greater (move to left)
    } else {
      current = current->prev;
    }
  }

  // if the node was not found, return NULL
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
void destroy_node_bst(struct Node *node_to_destroy) {
  node_destructor(node_to_destroy);
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

// MARK: PUBLIC HELPER FUNCTIONS

// Compare two integers and return if the first one is bigger, smaller or equal.
int compare_int(void *data_one, void *data_two) {
  // the first integer is bigger
  if (*(int *)data_one > *(int *)data_two) {
    return 1;
  }
  // the first integer is smaller
  if (*(int *)data_one < *(int *)data_two) {
    return -1;
  }
  // the integers are equal
  return 0;
}

// Compare two strings and return if the first one is greater, smaller or equal.
int compare_str(void *data_one, void *data_two) {
  int comparison = strcmp(data_one, data_two);

  // the first string is greater
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
