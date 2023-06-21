#include "../include/binary_tree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

// Test the creation and destruction of a binary tree
void test_creation_and_destruction() {
  struct BinaryTree tree = new_binary_tree(compare_int);
  assert(tree.root == NULL);
  destroy_binary_tree(&tree);
}

// Test inserting elements into the binary tree and searching for them
void test_insert_and_search() {
  struct BinaryTree tree = new_binary_tree(compare_int);

  // insert 10 new nodes
  for (int data = 0; data < 10; ++data) {
    tree.insert(&tree, &data, sizeof(int));
  }

  // search for the newlly created nodes
  for (int data = 0; data < 10; ++data) {
    struct Node *found_node = tree.search(&tree, &data);

    // check the data inserted
    assert(found_node != NULL);
    assert(*(int *)found_node->data == data);
  }

  // search again, but in reverse
  for (int data = 9; data >= 0; --data) {
    struct Node *found_node = tree.search(&tree, &data);

    // check the data inserted
    assert(found_node != NULL);
    assert(*(int *)found_node->data == data);
  }

  destroy_binary_tree(&tree);
}

// Test comparing strings in the binary tree
void test_string_comparison() {
  struct BinaryTree tree = new_binary_tree(compare_str);

  char* data1 = "apple";
  char* data2 = "banana";
  char* data3 = "cherry";

  tree.insert(&tree, data1, strlen(data1) + 1);
  tree.insert(&tree, data2, strlen(data2) + 1);
  tree.insert(&tree, data3, strlen(data3) + 1);

  struct Node* found_node1 = tree.search(&tree, data1);
  struct Node* found_node2 = tree.search(&tree, data2);
  struct Node* found_node3 = tree.search(&tree, data3);

  assert(found_node1 != NULL);
  assert(strcmp(found_node1->data, data1) == 0);

  assert(found_node2 != NULL);
  assert(strcmp(found_node2->data, data2) == 0);

  assert(found_node3 != NULL);
  assert(strcmp(found_node3->data, data3) == 0);

  destroy_binary_tree(&tree);
}

int main() {
  test_creation_and_destruction();
  test_insert_and_search();
  test_string_comparison();
  printf("binary_tree.t .............. OK\n");
  return 0;
}
