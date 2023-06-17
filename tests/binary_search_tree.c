#include "../include/BinarySearchTree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the "insert_bst" and the "search_bst" functions.
void insert_and_search_bst() {
  // create a new instance of a LinkedList
  struct BinarySearchTree tree = binary_search_tree_constructor(compare_int);

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    tree.insert(&tree, &i, sizeof(i));
  }

  for (int i = 9; i > 0; --i) {
    // check if the nodes of the tree have been inserted
    // and retrieved corectly
    struct Node *node = tree.search(&tree, &i);
    assert(*(int *)node->data == i);
  }

  binary_search_tree_destructor(&tree);
}

// This will display the entire tree for visual testing
void print_inorder(struct Node *node) {
  if (node) {
    print_inorder(node->prev);
    printf("%d ", *(int *)node->data);
    print_inorder(node->next);
  }
}

// This test will test the binary search tree in order to make sure that the
// tree is completely safe to use in production. The purpose of this test is to
// make sure that the entire test will run without any errors, so checking the
// test will not be required.
void tests_cases_bst() {
  // create a new instance of a LinkedList
  struct BinarySearchTree tree = binary_search_tree_constructor(compare_int);

  int data = 51;
  tree.insert(&tree, &data, sizeof(data));
  data = 34;
  tree.insert(&tree, &data, sizeof(data));
  data = 78;
  tree.insert(&tree, &data, sizeof(data));
  data = 2;
  tree.insert(&tree, &data, sizeof(data));
  data = 50;
  tree.insert(&tree, &data, sizeof(data));
  data = 56;
  tree.insert(&tree, &data, sizeof(data));
  data = 89;
  tree.insert(&tree, &data, sizeof(data));
  data = 1;
  tree.insert(&tree, &data, sizeof(data));
  data = 30;
  tree.insert(&tree, &data, sizeof(data));
  data = 85;
  tree.insert(&tree, &data, sizeof(data));
  data = 92;
  tree.insert(&tree, &data, sizeof(data));

  // print_inorder(tree.root);
  // printf("\n=====================\n");

  binary_search_tree_destructor(&tree);
}

int main() {
  insert_and_search_bst();
  tests_cases_bst();
  printf("binary_search_tree.t ....... OK\n");
  return 0;
}
