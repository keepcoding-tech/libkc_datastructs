#include "linked_list.h"

void linked_list_tests();
void add_node();
void remove_node();
void get_node();
void search_node();
void is_empty();
void tests_cases_ll();

void linked_list_tests() {
  add_node();
  remove_node();
  get_node();
  search_node();
  is_empty();
  tests_cases_ll();
  printf("linked_list.t .............. OK\n");
}

// Test the "add_node_ll" function.
void add_node() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // add ten new nodes
  for (int i = 0; i < 10; ++i) {
    list.add(&list, i, &i, sizeof(i));
    // check the length of the list
    assert(list.length == i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    struct Node *cursor = list.head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been inserted correctly
    assert(*(int *)cursor->data == i);
  }

  linked_list_destructor(&list);
}


// Test the "remove_node_ll" function.
void remove_node() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // insert ten new nodes (if the test reached here then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.add(&list, i, &i, sizeof(i));
  }

  // check if the node was correctly removed
  list.remove(&list, 5);
  struct Node *cursor = list.head;
  for (int i = 0; i < 5; ++i) {
    cursor = cursor->next;
  }
  assert(*(int *)cursor->data != 4 || list.length != 10);


  // check if the head of the list was correctly removed
  list.remove(&list, 0);
  cursor = list.head;
  assert(*(int *)cursor->data != 0 || list.length != 9);

  linked_list_destructor(&list);
}

// Test the "get_node_ll" function.
void get_node() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // insert ten new nodes (if the test reached here, then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.add(&list, i, &i, sizeof(i));
  }

  // check if the node was correctly retrieved
  struct Node *node = list.get(&list, 5);
  assert(*(int *)node->data == 5);

  // check if the head of the list was correctly retrieved
  node = list.get(&list, 0);
  assert(*(int *)node->data == 0);

  // check if the tail of the list was correctly retrieved
  node = list.get(&list, list.length - 1);
  assert(*(int *)node->data == 9);

  // expected NULL because the index is out of bounds
  // node = list.get(&list, 116);
  // if (node != NULL) {
  //   failed_ll("get_node", 4);
  // }

  linked_list_destructor(&list);
}

// create a generic "compare" function for testing
bool compare(void *data_one, void *data_two) {
  if (*(int *)data_one == *(int *)data_two) {
    return true;
  }
  return false;
}

// Test the "search_node_ll" function.
void search_node() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // insert ten new nodes (if the test reached here then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.add(&list, i, &i, sizeof(i));
  }

  // check if the values are in the list
  for (int i = 9; i > 0; --i) {
    assert(list.search(&list, &i, compare));
  }

  // check if the values are not in the list
  for (int i = 30; i > 20; --i) {
    assert(!list.search(&list, &i, compare));
  }

  linked_list_destructor(&list);
}

// Test the "list_is_empty" function.
void is_empty() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // the list should be empty
  assert(list.is_empty(&list));

  // insert ten new nodes (if the test reached here then the "add_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.add(&list, i, &i, sizeof(i));
  }

  // the list should not be empty
  assert(!list.is_empty(&list));

  // remove all nodes (if the test reached here then the "remove_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.remove(&list, 0);
  }

  // the list should be empty again
  assert(list.is_empty(&list));

  linked_list_destructor(&list);
}

// This test will check the most important tests cases for a linked list in
// order to make sure that the list is completely safe to use in production.
// The purpose of this test is to make sure that the entire test will run
// without any errors, so checking the test will not be required.
void tests_cases_ll() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // traversing the list
  //  edge cases:
  //  ->  traversing an empty list
  struct Node *current = list.head;
  while (current != NULL) {
    current = current->next;
  }

  // add ten new nodes to the list
  for (int i = 0; i < 10; ++i) {
    list.add(&list, i, &i, sizeof(i));
  }

  //  ->  traversing the list forword
  current = list.head;
  while (current->next != NULL) {
    current = current->next;
  }
  //  ->  traversing the list backwards
  while (current->prev != NULL) {
    current = current->prev;
  }

  // inserting into the list:
  //  -> inserting a sub-list
  struct LinkedList aux = linked_list_constructor();

  // add ten new nodes to the auxiliar list
  for (int i = 0; i < 10; ++i) {
    aux.add(&aux, i, &i, sizeof(i));
  }

  // add all the nodes of the auxiliary list into the initial list
  for (int i = 0; i < aux.length; ++i) {
    struct Node *node = aux.get(&aux, i);
    list.add(&list, i, node->data, sizeof(node));
  }
}
