// open source c library
// ==================================
//
// binary_tree.h
//
// Daniel Tanase
// 21/06/2023

/*
 * The Binary Tree structure is made up of Nodes, which hold references to
 * at most two children. The left child contains data values that are smaller
 * than the parent, while the right child contains values greater than the
 * parent.
 *
 * When creating a BinaryTree, users need to define their own comparison
 * function for the tree. It's important to note that these functions should
 * compare the data stored in the Nodes, not the Nodes themselves.
 *
 * To make things easier, there are some generic comparison functions available
 * for users to utilize.
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "node.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct BinaryTree {
  // head points to the top-most node in the tree
  struct Node* root;

  // the "compare" function is provided by the user and is responsible for
  // comparing the data of two nodes. This function must accept two void
  // pointers as arguments and return either 1, -1, or 0.
  int (*compare)(void* data_one, void* data_two);

  // adds new items to the tree
  void (*insert)(struct BinaryTree* self, void* data, size_t size);

  // finds a node in the tree, returning its data or NULL if not found
  struct Node* (*search)(struct BinaryTree* self, void* data);
};

// the constructor should be used to create binary search trees
struct BinaryTree* new_binary_tree(
    int (*compare)(void* data_one, void* data_two));

// the destructor should be used to destroy binary search trees
void destroy_binary_tree(struct BinaryTree* binary_tree);

// compare two integers and return if the first one is bigger, smaller or equal
int btree_compare_int(void* data_one, void* data_two);

// compare two strings and return if the first one is greater, smaller or equal
int btree_compare_str(void* data_one, void* data_two);

#endif /* BINARY_TREE_H */
