// This file is part of libkc_datastructs
// ==================================
//
// list.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Test the creation and destruction of a linked list.
void test_creation_and_destruction() {
  struct List* list = new_list();
  assert(list->head == NULL);
  assert(list->tail == NULL);
  destroy_list(list);
}

// Test case for the back() method.
void test_back() {
  // create a new instance of a List
  struct List* list = new_list();

  // there shouldn't be any nodes
  assert(list->back(list) == NULL);

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));

    // check if the last element is returned correctly
    struct Node* back = list->back(list);
    assert(*(int*)back->data == i);
  }

  // remove all the nodes
  for (int i = 9; i >= 0; --i) {
    // check if the last element is returned correctly
    struct Node* back = list->back(list);
    assert(*(int*)back->data == i);

    list->erase(list, i);
  }

  destroy_list(list);
}

// Test case for the clear() method.
void test_clear() {
  // create a new instance of a List
  struct List* list = new_list();

  // the list should be empty
  assert(list->empty(list));

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));
  }

  // the list should not be empty now
  assert(list->length == 10);
  assert(list->empty(list) == false);

  // clear the list
  list->clear(list);

  // the list should be empty again
  assert(list->empty(list));

  destroy_list(list);
}

// Test case for the empty() method.
void test_empty() {
  // create a new instance of a List
  struct List* list = new_list();

  // the list should be empty
  assert(list->empty(list));

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));
  }

  // the list should not be empty
  assert(!list->empty(list));

  // remove all nodes
  for (int i = 0; i < 10; ++i) {
    list->erase(list, 0);
  }

  // the list should be empty again
  assert(list->empty(list));

  destroy_list(list);
}

// Test case for the remove() method.
void test_erase() {
  // create a new instance of a List
  struct List* list = new_list();

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));
  }

  // remove the node from position 5
  list->erase(list, 5);

  // check if the node was correctly removed
  struct Node* cursor = list->head;
  for (int i = 0; i < 5; ++i) {
    cursor = cursor->next;
  }

  assert(*(int*)cursor->data != 4 || list->length != 10);

  // remove the head of the list
  list->erase(list, 0);

  // check if the head of the list was correctly removed
  cursor = list->head;
  assert(*(int*)cursor->data != 0 || list->length != 9);

  // remove the remaining nodes in reverse
  for (int i = list->length - 1; i >= 0; --i) {
    list->erase(list, i);
    assert(list->length == i);
  }

  destroy_list(list);
}

// Test case for the front() method.
void test_front() {
  // create a new instance of a List
  struct List* list = new_list();

  // there shouldn't be any nodes
  assert(list->front(list) == NULL);

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));

    // check if the first element is returned correctly,
    // it should always be zero (the same value)
    struct Node* front = list->front(list);
    assert(*(int*)front->data == 0);
  }

  // remove all the nodes
  for (int i = 0; i < 10; ++i) {
    // check if the first element is returned correctly
    struct Node* front = list->front(list);
    assert(*(int*)front->data == i);

    // erase only the first node for each iteration
    list->erase(list, 0);
  }

  destroy_list(list);
}

// Test case for the get() method.
void test_get() {
  // create a new instance of a List
  struct List* list = new_list();

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));
  }

  // check if the node was correctly retrieved
  struct Node* node = list->get(list, 5);
  assert(*(int*)node->data == 5);

  // check if the head of the list was correctly retrieved
  node = list->get(list, 0);
  assert(*(int*)node->data == 0);

  // check if the tail of the list was correctly retrieved
  node = list->get(list, list->length - 1);
  assert(*(int*)node->data == 9);

  destroy_list(list);
}

// Test case for the add() method.
void test_insert() {
  // create a new instance of a List
  struct List* list = new_list();

  // add ten new nodes of type int
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));

    // check the length of the list
    assert(list->length == i + 1);
  }

  // add ten new nodes of type char
  for (int i = 10; i < 20; ++i) {
    char c = 'a' + i;
    list->insert(list, i, &c, sizeof(char));

    // check the length of the list
    assert(list->length == i + 1);
  }

  for (int i = 0; i < 20; ++i) {
    struct Node* cursor = list->head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been inserted correctly
    if (i < 10) {
      assert(*(int*)cursor->data == i);
    } else {
      assert(*(char*)cursor->data == 'a' + i);
    }
  }

  // add a new node of type int[] (array)
  int nums[] = {1, 2, 3, 4, 5};
  size_t size = sizeof(nums) / sizeof(nums[0]);
  list->insert(list, 20, &nums, sizeof(int) * size);

  // get the 21st node
  struct Node* cursor = list->tail;

  // check if the node has been inserted correctly
  int* ptr = (int*)cursor->data;
  for (int i = 0; i < size; ++i) {
    assert(ptr[i] == nums[i]);
  }

  destroy_list(list);
}

// Test case for the pop_back() method.
void test_pop_back() {
  // create a new instance of a List
  struct List* list = new_list();

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));
  }

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    // the length should be reduced only after the pop
    assert(*(int*)list->tail->data == 10 - (i + 1));
    assert(list->length == 10 - i);

    list->pop_back(list);

    // check if the last node was deleted correctly
    assert(list->length == 10 - (i + 1));
  }

  destroy_list(list);
}

// Test case for the pop_front() method.
void test_pop_front() {
  // create a new instance of a List
  struct List* list = new_list();

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));
  }

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    // the length should be reduced only after the pop
    assert(*(int*)list->head->data == i);
    assert(list->length == 10 - i);

    list->pop_front(list);

    // check if the last node was deleted correctly
    assert(list->length == 10 - (i + 1));
  }

  destroy_list(list);
}

// Test case for the push_back() method.
void test_push_back() {
  // create a new instance of a List
  struct List* list = new_list();

  // push back ten new nodes
  for (int i = 0; i < 10; ++i) {
    // the length should be incremented only after push
    assert(list->length == i);

    list->push_back(list, &i, sizeof(int));

    // check if the node was inserted correctly
    assert(*(int*)list->tail->data == i);
    assert(list->length == i + 1);
  }

  destroy_list(list);
}

// Test case for the push_front() method.
void test_push_front() {
  // create a new instance of a List
  struct List* list = new_list();

  // push back ten new nodes
  for (int i = 0; i < 10; ++i) {
    // the length should be incremented only after push
    assert(list->length == i);

    list->push_front(list, &i, sizeof(int));

    // check if the node was inserted correctly
    assert(*(int*)list->head->data == i);
    assert(list->length == i + 1);
  }

  destroy_list(list);
}

// Test case for the search() and remove() method.
int compare(const void* data_one, const void* data_two) {
  return (*(int*)data_one - *(int*)data_two);
}

// Test case for the remove() method.
void test_remove() {
  // create a new instance of a List
  struct List* list = new_list();

  // use the same data
  int data = 10;

  // add 5 new nodes
  for (int i = 0; i < 5; ++i) {
    list->insert(list, i, &data, sizeof(int));
  }

  data = 20;

  // add 5 new nodes
  for (int i = 5; i < 10; ++i) {
    list->insert(list, i, &data, sizeof(int));
  }

  // should remove only 5 nodes
  list->remove(list, &data, compare);
  assert(list->length == 5);

  data = 10;

  // should remove all 5 nodes
  list->remove(list, &data, compare);
  assert(list->empty(list));

  destroy_list(list);
}

// Test case for the search() method.
void test_search() {
  // create a new instance of a List
  struct List* list = new_list();

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->insert(list, i, &i, sizeof(int));
  }

  // check if the values are in the list
  for (int i = 9; i > 0; --i) {
    assert(list->search(list, &i, compare));
  }

  // check if the values are not in the list
  for (int i = 30; i > 20; --i) {
    assert(!list->search(list, &i, compare));
  }

  destroy_list(list);
}

COMPARE_LIST(int, compare_int)
COMPARE_LIST(char, compare_char)
COMPARE_LIST(int8_t, compare_int8_t)

void test_compare() {
  int a_int = 1, b_int = 2;
  assert(compare_int(&a_int, &b_int) < 0);
  a_int = 2, b_int = 1;
  assert(compare_int(&a_int, &b_int) > 0);
  a_int = 1, b_int = 1;
  assert(compare_int(&a_int, &b_int) == 0);

  char a_char = 'a', b_char = 'b';
  assert(compare_char(&a_char, &b_char) < 0);
  a_char = 'b', b_char = 'a';
  assert(compare_char(&a_char, &b_char) > 0);
  a_char = 'a', b_char = 'a';
  assert(compare_char(&a_char, &b_char) == 0);

  int8_t a_int8_t = 1, b_int8_t = 2;
  assert(compare_int8_t(&a_int8_t, &b_int8_t) < 0);
  a_int8_t = 2, b_int8_t = 1;
  assert(compare_int8_t(&a_int8_t, &b_int8_t) > 0);
  a_int8_t = 1, b_int8_t = 1;
  assert(compare_int8_t(&a_int8_t, &b_int8_t) == 0);
}

int main() {
  test_creation_and_destruction();
  test_back();
  test_clear();
  test_empty();
  test_erase();
  test_front();
  test_get();
  test_insert();
  test_pop_back();
  test_pop_front();
  test_push_back();
  test_push_front();
  test_remove();
  test_search();
  test_compare();
  printf("list.t ..................... OK\n");
  return 0;
}
