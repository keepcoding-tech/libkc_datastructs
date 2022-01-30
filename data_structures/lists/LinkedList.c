/*
 Note: due to the fact that several data structures (in this project) will have
 functions for "insertion", "retrieving", "removing", etc; the name of the
 functions in the implementation of the library will have the notation of "ll"
 at the end, representing -> "linked list".
*/

#include "LinkedList.h"

// MARK: PUBLIC MEMBER METHODS

void insert_node_ll(struct LinkedList *linked_list,
  int index, void *data, unsigned long size);
void remove_node_ll(struct LinkedList *linked_list, int index);
struct Node * retrieve_node_ll(struct LinkedList *linked_list, int index);

// MARK: PRIVATE MEMBER METHODS

struct Node * create_node_ll(void *data, unsigned long size);
void destroy_node_ll(struct Node *node_to_destroy);
struct Node * iterate_ll(int index, struct LinkedList *linked_list);

// The constructor is used to create new instances of linked list.
struct LinkedList linked_list_constructor() {
  // create a LinkedList instance to be returned
  struct LinkedList new_list;

  // initialize the structure members fields
  new_list.head = NULL;
  new_list.length = 0;

  // assigns the public member methods
  new_list.insert = insert_node_ll;
  new_list.remove = remove_node_ll;
  new_list.retrieve = retrieve_node_ll;

  return new_list;
}

// The destructor removes all the nodes by freeing the nodes instances and data.
void linked_list_destructor(struct LinkedList *linked_list) {
  // access the linked list length only once
  int list_length = linked_list->length;
  for (int i = 0; i < list_length; ++i) {
    linked_list->remove(linked_list, 0);
  }
}

// The "insert_node_ll" function puts a new node in the chain.
void insert_node_ll(struct LinkedList *linked_list,
  int index, void *data, unsigned long size) {

  // create a new node to be inserted
  struct Node *new_node = create_node_ll(data, size);

  // check if this node will be the new head of the list
  if (index == 0) {
    // define the node's "next"
    new_node->next = linked_list->head;
    // re-define the list's "head"
    linked_list->head = new_node;
  } else {
    // find the item in the list immediately before the desired index
    struct Node *cursor = iterate_ll(index - 1, linked_list);
    // set the node's "next" and "prev" to the corresponding nodes
    new_node->next = cursor->next;
    new_node->prev = cursor;
    // set the cursor's "next" to the new node
    cursor->next = new_node;
  }

  // increment the list length
  ++linked_list->length;
}

// The "remove_node_ll" function removes a node from the linked list.
void remove_node_ll(struct LinkedList *linked_list, int index) {
  // check if the item being removed is the head
  if (index == 0) {
    // collect the node to be removed
    struct Node *node_to_remove = linked_list->head;
    // define the new "head" of the list
    if (node_to_remove) {
      linked_list->head = node_to_remove->next;
      // remove the desired node
      destroy_node_ll(node_to_remove);
    }
  } else {
    // find the node in the list before the one that is going to be removed
    struct Node *cursor = iterate_ll(index - 1, linked_list);
    // use the cursor to define the node to be removed
    struct Node *node_to_remove = cursor->next;
    // update the cursor's "next" to skip the node to be removed
    cursor->next = node_to_remove->next;
    // the "prev" of the third node must point to the current node
    node_to_remove->next->prev = node_to_remove->prev;
    // remove the node
    destroy_node_ll(node_to_remove);
  }

  // decrement the list length
  --linked_list->length;
}

// The "retrieve_node_ll" function is used to access data in the list.
struct Node * retrieve_node_ll(struct LinkedList *linked_list, int index) {
  // find the desired node and return its data
  struct Node *node = iterate_ll(index, linked_list);

  if (node) {
    return node;
  }
  return NULL;
}

// The "create_node_ll" function creates a new node to add to the chain by
// allocating space on the heap and calling the node constructor.
struct Node * create_node_ll(void *data, unsigned long size) {
  // allocate space
  struct Node *new_node = malloc(sizeof *new_node);
  // call the constructor
  *new_node = node_constructor(data, size);

  return new_node;
}

// The "destroy_node_ll" function removes a node by deallocating it's memory
// address, this simply renames the node destructor function.
void destroy_node_ll(struct Node *node) {
  node_destructor(node);
}

// The "iterate_ll" function traverses the list from beginning to end.
struct Node * iterate_ll(int index, struct LinkedList *linked_list) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= linked_list->length) {
    // TODO: return error insted of printing it
    printf("Index out of bound...\n");
    return NULL;
  }

  // create a cursor node for iteration
  struct Node *cursor = linked_list->head;
  // step through the list until the desired index is reached
  for (int i = 0; i < index; ++i) {
    cursor = cursor->next;
  }

  return cursor;
}
