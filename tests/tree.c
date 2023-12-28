// This file is part of libkc_datastructs
// ==================================
//
// tree.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc/testing/testing.h"
#include "../include/tree.h"
#include "../include/pair.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

COMPARE_TREE(int, btree_compare_int)
COMPARE_TREE(char, btree_compare_str)

// use this function for testing a custom compare function
int compare(const void* a, const void* b)
{
  return (*(int*)(((struct Pair*)a)->key) -
    *(int*)(((struct Pair*)b)->key));
}

int main() {
  testgroup("Tree")
  {
    subtest("test creation and destruction")
    {
      struct Tree* tree = new_tree(btree_compare_int);
      ok(tree->root == NULL);
      destroy_tree(tree);
    }

    subtest("test insert and search")
    {
      struct Tree* tree = new_tree(btree_compare_int);

      // insert 30 new nodes
      for (int data = 0; data < 30; ++data)
      {
        tree->insert(tree, &data, sizeof(int));
      }

      // search for the newlly created nodes
      for (int data = 0; data < 30; ++data)
      {
        struct Node* found_node = tree->search(tree, &data);

        // check the data inserted
        ok(found_node != NULL);
        ok(*(int*)found_node->data == data);
      }

      // search again, but in reverse
      for (int data = 29; data >= 0; --data)
      {
        struct Node* found_node = tree->search(tree, &data);

        // check the data inserted
        ok(found_node != NULL);
        ok(*(int*)found_node->data == data);
      }

      destroy_tree(tree);
    }

    subtest("test remove")
    {
      struct Tree* tree = new_tree(btree_compare_int);
      int data[] = { 50, 30, 60, 20, 70, 15, 75, 25, 65 };

      // insert nodes for all test cases
      for (int i = 0; i < 9; ++i)
      {
        tree->insert(tree, &data[i], sizeof(int));
      }

      // test case 1: remove node with 2 children
      int remove = 20;
      tree->remove(tree, &remove, sizeof(int));
      struct Node* found_node = tree->root->prev->prev;
      ok(*(int*)found_node->data == 25);
      ok(*(int*)found_node->prev->data == 15);
      ok(found_node->next == NULL);

      // test case 2: remove node with 1 child
      remove = 60;
      tree->remove(tree, &remove, sizeof(int));
      found_node = tree->root->next;
      ok(*(int*)found_node->data == 70);
      ok(*(int*)found_node->prev->data == 65);
      ok(*(int*)found_node->next->data == 75);

      // test case 3: remove node with 0 children
      remove = 75;
      tree->remove(tree, &remove, sizeof(int));
      found_node = tree->root->next;
      ok(*(int*)found_node->data == 70);
      ok(*(int*)found_node->prev->data == 65);
      ok(found_node->next == NULL);

      // test case 4: remove root node
      remove = 50;
      tree->remove(tree, &remove, sizeof(int));
      found_node = tree->root;
      ok(*(int*)found_node->data == 65);
      ok(*(int*)found_node->prev->data == 30);
      ok(*(int*)found_node->next->data == 70);

      destroy_tree(tree);
    }

    subtest("test string comparison")
    {
      struct Tree* tree = new_tree(btree_compare_str);

      char* data1 = "apple";
      char* data2 = "banana";
      char* data3 = "cherry";

      tree->insert(tree, data1, strlen(data1) + 1);
      tree->insert(tree, data2, strlen(data2) + 1);
      tree->insert(tree, data3, strlen(data3) + 1);

      struct Node* found_node1 = tree->search(tree, data1);
      struct Node* found_node2 = tree->search(tree, data2);
      struct Node* found_node3 = tree->search(tree, data3);

      ok(found_node1 != NULL);
      ok(strcmp(found_node1->data, data1) == 0);

      ok(found_node2 != NULL);
      ok(strcmp(found_node2->data, data2) == 0);

      ok(found_node3 != NULL);
      ok(strcmp(found_node3->data, data3) == 0);

      destroy_tree(tree);
    }

    subtest("test custom comparison")
    {
      struct Tree* tree = new_tree(compare);

      // create a new Pair
      int key = 10, val = 100;
      struct Pair* pair = pair_constructor(&key, sizeof(int), &val, sizeof(int));

      // insert the new pair
      tree->insert(tree, pair, sizeof(struct Pair));

      // check if the pair was inserted and found corectlly
      struct Node* found_node = tree->search(tree, pair);
      struct Pair* found_pair = (struct Pair*)found_node->data;

      ok(found_pair != NULL);
      ok(*(int*)found_pair->key == key);
      ok(*(int*)found_pair->value == val);

      // check the remove function
      tree->remove(tree, pair, sizeof(struct Pair));
      ok(tree->root == NULL);

      pair_destructor(pair);
      destroy_tree(tree);
    }

    done_testing()
  }

  return 0;
}
