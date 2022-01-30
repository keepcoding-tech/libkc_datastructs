#include "linked_list.h"

void linked_list_tests();

void insert_node();
void remove_node();
void retrieve_node();

void linked_list_tests() {
  insert_node();
  remove_node();
  retrieve_node();
  printf("linked_list.t .............. OK\n");
}

// Display where the test failed.
void failed_ll(char *test, int line) {
  printf("FAIELD -> %s at line %d\n", test, line);
  exit(1);
}

// Test the "insert_node_ll" function.
void insert_node() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // insert ten new nodes
  for (int i = 0; i < 10; ++i) {
    list.insert(i, &i, &list, sizeof(i));
    // check the length of the list
    if (list.length != i + 1) {
      failed_ll("insert_node", 32);
    }
  }

  for (int i = 0; i < 10; ++i) {
    struct Node *cursor = list.head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been inserted correctly
    if (*(int *)cursor->data != i) {
      failed_ll("insert_node", 44);
    }
  }

  linked_list_destructor(&list);
}


// Test the "remove_node_ll" function.
void remove_node() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // insert ten new nodes (if the test reached here then the "insert_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.insert(i, &i, &list, sizeof(i));
  }

  // check if the node was correctly removed
  list.remove(5, &list);
  struct Node *cursor = list.head;
  for (int i = 0; i < 5; ++i) {
    cursor = cursor->next;
  }
  if (*(int *)cursor->data == 4 || list.length == 10) {
    failed_ll("remove_node", 70);
  }


  // check if the head of the list was correctly removed
  list.remove(0, &list);
  cursor = list.head;
  if (*(int *)cursor->data == 0 || list.length == 9) {
    failed_ll("remove_node", 78);
  }

  linked_list_destructor(&list);
}

// Test the "retrieve_node_ll" function.
void retrieve_node() {
  // create a new instance of a LinkedList
  struct LinkedList list = linked_list_constructor();

  // insert ten new nodes (if the test reached here, then the "insert_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.insert(i, &i, &list, sizeof(i));
  }

  // check if the node was correctly retrieved
  struct Node *node = list.retrieve(5, &list);
  if (*(int *)node->data != 5) {
    failed_ll("retrieve_node", 98);
  }

  // check if the head of the list was correctly retrieved
  node = list.retrieve(0, &list);
  if (*(int *)node->data != 0) {
    failed_ll("retrieve_node", 104);
  }

  // check if the tail of the list was correctly retrieved
  node = list.retrieve(list.length - 1, &list);
  if (*(int *)node->data != 9) {
    failed_ll("retrieve_node", 110);
  }

  // expected NULL because the index is out of bounds
  node = list.retrieve(100, &list);
  if (node != NULL) {
    failed_ll("retrieve_node", 116);
  }

  linked_list_destructor(&list);
}
