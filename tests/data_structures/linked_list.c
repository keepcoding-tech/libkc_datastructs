#include "linked_list.h"

void linked_list_tests();

void insert_node();
void remove_node();
void retrieve_node();
void search_node();

void linked_list_tests() {
  insert_node();
  remove_node();
  retrieve_node();
  search_node();
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
    list.insert(&list, i, &i, sizeof(i));
    // check the length of the list
    if (list.length != i + 1) {
      failed_ll("insert_node", 34);
    }
  }

  for (int i = 0; i < 10; ++i) {
    struct Node *cursor = list.head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been inserted correctly
    if (*(int *)cursor->data != i) {
      failed_ll("insert_node", 46);
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
    list.insert(&list, i, &i, sizeof(i));
  }

  // check if the node was correctly removed
  list.remove(&list, 5);
  struct Node *cursor = list.head;
  for (int i = 0; i < 5; ++i) {
    cursor = cursor->next;
  }
  if (*(int *)cursor->data == 4 || list.length == 10) {
    failed_ll("remove_node", 72);
  }


  // check if the head of the list was correctly removed
  list.remove(&list, 0);
  cursor = list.head;
  if (*(int *)cursor->data == 0 || list.length == 9) {
    failed_ll("remove_node", 80);
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
    list.insert(&list, i, &i, sizeof(i));
  }

  // check if the node was correctly retrieved
  struct Node *node = list.retrieve(&list, 5);
  if (*(int *)node->data != 5) {
    failed_ll("retrieve_node", 100);
  }

  // check if the head of the list was correctly retrieved
  node = list.retrieve(&list, 0);
  if (*(int *)node->data != 0) {
    failed_ll("retrieve_node", 106);
  }

  // check if the tail of the list was correctly retrieved
  node = list.retrieve(&list, list.length - 1);
  if (*(int *)node->data != 9) {
    failed_ll("retrieve_node", 112);
  }

  // expected NULL because the index is out of bounds
  // node = list.retrieve(&list, 116);
  // if (node != NULL) {
  //   failed_ll("retrieve_node", 118);
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

  // insert ten new nodes (if the test reached here then the "insert_node"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    list.insert(&list, i, &i, sizeof(i));
  }

  // check if the values are in the list
  for (int i = 9; i > 0; --i) {
    if (!list.search(&list, &i, compare)) {
      failed_ll("search_node", 143);
    }
  }

  // check if the values are not in the list
  for (int i = 30; i > 20; --i) {
    if (list.search(&list, &i, compare)) {
      failed_ll("search_node", 149);
    }
  }

  linked_list_destructor(&list);
}
