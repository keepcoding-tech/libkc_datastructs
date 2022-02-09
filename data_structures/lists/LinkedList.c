/*
 Note: due to the fact that several data structures (in this project) will have
 functions for "insertion", "retrieving", "removing", etc; the name of the
 functions in the implementation of the library will have the notation of "ll"
 at the end, representing -> "linked list".
*/

#include "LinkedList.h"

// MARK: PUBLIC MEMBER METHODS

void add_node_ll(struct LinkedList *self,
  int index, void *data, unsigned long size);
struct Node * get_node_ll(struct LinkedList *self, int index);
bool list_is_empty(struct LinkedList *self);
void remove_node_ll(struct LinkedList *self, int index);
bool search_node_ll(struct LinkedList *self, void *query,
  bool (*compare)(void *data_one, void *data_two));

// MARK: PRIVATE MEMBER METHODS

struct Node * create_node_ll(void *data, unsigned long size);
void destroy_node_ll(struct Node *node_to_destroy);
struct Node * iterate_ll(struct LinkedList *linked_list, int index);

// The constructor is used to create new instances of linked list.
struct LinkedList linked_list_constructor() {
  // create a LinkedList instance to be returned
  struct LinkedList new_list;

  // initialize the structure members fields
  new_list.head = NULL;
  new_list.length = 0;

  // assigns the public member methods
  new_list.add = add_node_ll;
  new_list.get = get_node_ll;
  new_list.is_empty = list_is_empty;
  new_list.remove = remove_node_ll;
  new_list.search = search_node_ll;

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

// The "add_node_ll" function puts a new node in the chain.
void add_node_ll(struct LinkedList *self,
  int index, void *data, unsigned long size) {

  // create a new node to be inserted
  struct Node *new_node = create_node_ll(data, size);

  // check if this node will be the new head of the list
  if (index == 0) {
    // define the node's "next"
    new_node->next = self->head;
    // re-define the list's "head"
    self->head = new_node;
  } else {
    // find the item in the list immediately before the desired index
    struct Node *cursor = iterate_ll(self, index - 1);
    // set the node's "next" and "prev" to the corresponding nodes
    new_node->next = cursor->next;
    new_node->prev = cursor;
    // set the cursor's "next" to the new node
    cursor->next = new_node;
    // the "prev" of the third node must point to the new node
    if (new_node->next) {
      new_node->next->prev = new_node;
    }
  }

  // increment the list length
  ++self->length;
}

// The "get_node_ll" function is used to access data in the list.
struct Node * get_node_ll(struct LinkedList *self, int index) {
  // find the desired node and return its data
  struct Node *node = iterate_ll(self, index);

  if (node) {
    return node;
  }
  return NULL;
}

// The "list_is_empty" will return either if the list is empty or not
bool list_is_empty(struct LinkedList *self) {
  return self->length == 0 && !self->head;
}

// The "remove_node_ll" function removes a node from the linked list.
void remove_node_ll(struct LinkedList *self, int index) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    // TODO: return error insted of printing it
    printf("Index out of bound...\n");
    return;
  }

  // get the "head" of the list
  struct Node *current = self->head;

  // check if the item being removed is the "head"
  if (index == 0) {
    // define the new "head" of the list
    self->head = current->next;
    destroy_node_ll(current);
  } else {
    // find the node in the list before the one that is going to be removed
    current = iterate_ll(self, index - 1);
    // use the node returned to define the node to be removed
    struct Node *node_to_remove = current->next;
    // update the current node "next" to skip the node to be removed
    current->next = node_to_remove->next;
    // the "prev" of the third node must point to the current node
    current->next->prev = current;

    // remove the node
    destroy_node_ll(node_to_remove);
  }

  // decrement the list length
  --self->length;
}

// The "search_node_ll" function searchs for a specific node by data
bool search_node_ll(struct LinkedList *self, void *query,
  bool (*compare)(void *data_one, void *data_two)) {
  // create a new node instance
  struct Node *node = self->head;

  // search the node by value
  while (node) {
    if (compare(node->data, query)) {
      return true;
    }
    node = node->next;
  }

  return false;
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
void destroy_node_ll(struct Node *node_to_destroy) {
  node_destructor(node_to_destroy);
}

// The "iterate_ll" function traverses the list from beginning to end.
struct Node * iterate_ll(struct LinkedList *linked_list, int index) {
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
