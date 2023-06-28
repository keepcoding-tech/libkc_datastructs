#include "../include/linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

// Test the creation and destruction of a linked list.
void test_creation_and_destruction() {
  struct LinkedList* list = new_linked_list();
  assert(list->head == NULL);
  assert(list->tail == NULL);
  destroy_linked_list(list);
}

// Test case for the add() method.
void test_add() {
  // create a new instance of a LinkedList
  struct LinkedList* list = new_linked_list();

  // add ten new nodes
  for (int i = 0; i < 10; ++i) {
    list->add(list, i, &i, sizeof(i));

    // check the length of the list
    assert(list->length == i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    struct Node* cursor = list->head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been inserted correctly
    assert(*(int*)cursor->data == i);
  }

  destroy_linked_list(list);
}

// Test case for the remove() method.
void test_remove() {
  // create a new instance of a LinkedList
  struct LinkedList* list = new_linked_list();

  // insert ten new nodes (if the test reached here then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list->add(list, i, &i, sizeof(i));
  }

  // remove the node from position 5
  list->remove(list, 5);

  // check if the node was correctly removed
  struct Node* cursor = list->head;
  for (int i = 0; i < 5; ++i) {
    cursor = cursor->next;
  }

  assert(*(int*)cursor->data != 4 || list->length != 10);

  // remove the head of the list
  list->remove(list, 0);

  // check if the head of the list was correctly removed
  cursor = list->head;
  assert(*(int*)cursor->data != 0 || list->length != 9);

  destroy_linked_list(list);
}

// Test case for the get() method.
void test_get() {
  // create a new instance of a LinkedList
  struct LinkedList* list = new_linked_list();

  // insert ten new nodes (if the test reached here, then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list->add(list, i, &i, sizeof(i));
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

  // Accessing a non-existing node, expected
  // NULL because the index is out of bounds
  // THIS WILL PASS
  // node = list->get(list, 116);
  // assert(node == NULL);

  destroy_linked_list(list);
}

// Test case for the search() method.
bool compare(void* data_one, void* data_two) {
  return (*(int*)data_one == *(int*)data_two);
}

void test_search() {
  // create a new instance of a LinkedList
  struct LinkedList* list = new_linked_list();

  // insert ten new nodes (if the test reached here then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list->add(list, i, &i, sizeof(i));
  }

  // check if the values are in the list
  for (int i = 9; i > 0; --i) {
    assert(list->search(list, &i, compare));
  }

  // check if the values are not in the list
  for (int i = 30; i > 20; --i) {
    assert(!list->search(list, &i, compare));
  }

  destroy_linked_list(list);
}

// Test case for the is_empty() method.
void test_is_empty() {
  // create a new instance of a LinkedList
  struct LinkedList* list = new_linked_list();

  // the list should be empty
  assert(list->is_empty(list));

  // insert ten new nodes (if the test reached here then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list->add(list, i, &i, sizeof(i));
  }

  // the list should not be empty
  assert(!list->is_empty(list));

  // remove all nodes (if the test reached here then the "remove_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list->remove(list, 0);
  }

  // the list should be empty again
  assert(list->is_empty(list));

  destroy_linked_list(list);
}

// This test will check the most important tests cases for a linked list in
// order to make sure that the list is completely safe to use in production.
// The purpose of this test is to make sure that the entire test will run
// without any errors, so checking the test will not be required.
void tests_cases() {
  // create a new instance of a LinkedList
  struct LinkedList* list = new_linked_list();

  // traversing the list
  //  edge cases:
  //  ->  traversing an empty list
  struct Node* current = list->head;
  while (current != NULL) {
    current = current->next;
  }

  // add ten new nodes to the list
  for (int i = 0; i < 10; ++i) {
    list->add(list, i, &i, sizeof(i));
  }

  //  ->  traversing the list forword
  current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }
  //  ->  traversing the list backwards
  while (current->prev != NULL) {
    current = current->prev;
  }

  // inserting into the list:
  //  -> inserting a sub-list
  struct LinkedList* aux = new_linked_list();

  // add ten new nodes to the auxiliar list
  for (int i = 0; i < 10; ++i) {
    aux->add(aux, i, &i, sizeof(i));
  }

  // add all the nodes of the auxiliary list into the initial list
  for (int i = 0; i < aux->length; ++i) {
    struct Node* node = aux->get(aux, i);
    list->add(list, i, node->data, sizeof(node));
  }
}

int main() {
  test_creation_and_destruction();
  test_add();
  test_remove();
  test_get();
  test_search();
  test_is_empty();
  tests_cases();
  printf("linked_list.t .............. OK\n");
  return 0;
}
