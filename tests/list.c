#include "../include/list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
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

// Test case for the search() method.
bool compare(void* data_one, void* data_two) {
  return (*(int*)data_one == *(int*)data_two);
}

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

int main() {
  test_creation_and_destruction();
  test_back();
  test_empty();
  test_erase();
  test_front();
  test_get();
  test_insert();
  test_search();
  printf("list.t ..................... OK\n");
  return 0;
}
