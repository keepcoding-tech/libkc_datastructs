#include "binary_search_tree.h"

void binary_search_tree_tests();

void insert_and_search_bst();

void binary_search_tree_tests() {
  insert_and_search_bst();
  printf("binary_search_tree.t ....... OK\n");
}

// Display where the test failed.
void failed_bst(char *test, int line) {
  printf("FAIELD -> %s at line %d\n", test, line);
  exit(1);
}

// Test the "insert_bst" and the "search_bst" functions.
void insert_and_search_bst() {
  // create a new instance of a LinkedList
  struct BinarySearchTree tree =
    binary_search_tree_constructor(binary_search_tree_str_compare);

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    tree.insert(&tree, &i, sizeof(i));
  }

  for (int i = 9; i > 0; --i) {
    // check if the nodes of the tree have been inserted
    // and retrieved corectly
    struct Node *node = tree.search(&tree, &i);
    if (*(int *)node->data != i) {
      failed_bst("insert_and_search_bst", 34);
    }
  }

  binary_search_tree_destructor(&tree);
}
