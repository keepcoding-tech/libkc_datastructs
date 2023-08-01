// open source c library
// ==================================
//
// tree.h
//
// Daniel Tanase
// 21/06/2023

/*
 * The Binary Tree structure is made up of Nodes, which hold references to
 * at most two children. The left child contains data values that are smaller
 * than the parent, while the right child contains values greater than the
 * parent.
 *
 * When creating a Tree, users need to define their own comparison
 * function for the tree. It's important to note that these functions should
 * compare the data stored in the Nodes, not the Nodes themselves.
 *
 * To make things easier, there are some generic comparison functions available
 * for users to utilize.
 */

#ifndef TREE_H
#define TREE_H

#include "node.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Tree {
  // root points to the top-most node in the tree
  struct Node* root;

  // the "compare" function is provided by the user and is responsible for
  // comparing the data of two nodes. This function must accept two void
  // pointers as arguments and return either 1 (or greater), -1 (or less), or 0.
  int (*compare)(const void* a, const void* b);

  // adds new items to the tree
  void (*insert)(struct Tree* self, void* data, size_t size);

  // removes a node by value
  void (*remove)(struct Tree* self, void* data, size_t size);

  // finds a node in the tree, returning its data or NULL if not found
  struct Node* (*search)(struct Tree* self, void* data);
};

// the constructor should be used to create binary search trees
struct Tree* new_tree(int (*compare)(const void* a, const void* b));

// the destructor should be used to destroy binary search trees
void destroy_tree(struct Tree* tree);

// use this macro to define any type of primitive data comparison function
#define COMPARE_TREE(type, function_name) \
  int function_name(const void* a, const void* b) { \
    if (*(type*)a < *(type*)b) {                    \
      return -1;                                    \
    }                                               \
    if (*(type*)a > *(type*)b) {                    \
      return 1;                                     \
    }                                               \
    return 0;                                       \
  }

#endif /* TREE_H */