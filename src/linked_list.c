#include "../include/linked_list.h"

// MARK: PUBLIC MEMBER METHODS
void add_node_ll(struct LinkedList* self, int index, void* data, size_t size);
struct Node* get_node_ll(struct LinkedList* self, int index);
bool is_empty_ll(struct LinkedList* self);
void remove_node_ll(struct LinkedList* self, int index);
bool search_node_ll(struct LinkedList* self, void* query,
  bool (*compare)(void* data_one, void* data_two));

// MARK: PRIVATE MEMBER METHODS
void destroy_node_ll(struct Node* node_to_destroy);
struct Node* iterate_ll(struct LinkedList* self, int index);

// The constructor is used to create new instances of linked list.
struct LinkedList* new_linked_list() {
  // create a LinkedList instance to be returned
  struct LinkedList* new_list = malloc(sizeof(struct LinkedList));

  // initialize the structure members fields
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->length = 0;

  // assigns the public member methods
  new_list->add = add_node_ll;
  new_list->get = get_node_ll;
  new_list->is_empty = is_empty_ll;
  new_list->remove = remove_node_ll;
  new_list->search = search_node_ll;

  return new_list;
}

// The destructor removes all the nodes by freeing the nodes instances and data.
void destroy_linked_list(struct LinkedList* linked_list) {
  // access the linked list length only once
  int list_length = linked_list->length;
  for (int i = 0; i < list_length; ++i) {
    linked_list->remove(linked_list, 0);
  }

  // free the linked list too
  free(linked_list);
}

// This function puts a new node in the chain.
void add_node_ll(struct LinkedList* self, int index, void* data, size_t size) {
  // create a new node to be inserted
  struct Node* new_node = node_constructor(data, size);

  // if the node is NULL, don't make the insertion
  if (new_node == NULL) {
    return;
  }

  // check if this node will be the new head
  if (index == 0) {
    // re-define the list's "head"
    new_node->next = self->head;
    self->head = new_node;

    // increment the list length
    ++self->length;
    return;
  }

  // find the item in the list immediately before the desired index
  struct Node* cursor = iterate_ll(self, index - 1);

  // set the node's "next" and "prev" to the corresponding nodes
  new_node->next = cursor->next;
  new_node->prev = cursor;

  // set the cursor's "next" to the new node
  cursor->next = new_node;

  // the "prev" of the third node must point to the new node
  if (new_node->next) {
    new_node->next->prev = new_node;
  }

  // check if this node will be the new tail
  if (index == self->length) {
    self->tail = new_node;
  }

  // increment the list length
  ++self->length;
}

// This function is used to access data in the list.
struct Node* get_node_ll(struct LinkedList* self, int index) {
  // find the desired node and return its data
  struct Node* node = iterate_ll(self, index);

  if (node) {
    return node;
  }

  // if no node found, return null
  return NULL;
}

// This function will return either if the list is empty or not
bool is_empty_ll(struct LinkedList* self) {
  return self->length == 0 && !self->head;
}

// This function removes a node from the linked list.
void remove_node_ll(struct LinkedList* self, int index) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    printf("keepcoding/LinkedList ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Index out of bound!\n");
    return;
  }

  // get the "head" of the list
  struct Node* current = self->head;

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
    current->next = node_to_remove->next;
    current->next->prev = current;

    // remove the node
    destroy_node_ll(node_to_remove);
  }

  // decrement the list length
  --self->length;
}

// This function searchs for a specific node by data.
bool search_node_ll(struct LinkedList* self, void* query,
  bool (*compare)(void* data_one, void* data_two)) {
  // create a new node instance
  struct Node* node = self->head;

  // search the node by value
  while (node) {
    if (compare(node->data, query)) {
      return true;
    }
    node = node->next;
  }

  return false;
}

// This function removes a node by deallocating it's memory
// address, this simply renames the node destructor function.
void destroy_node_ll(struct Node* node_to_destroy) {
  node_destructor(node_to_destroy);
}

// This function traverses the list from beginning to end.
struct Node* iterate_ll(struct LinkedList* self, int index) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    printf("keepcoding/LinkedList ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Index out of bound!\n");
    return NULL;
  }

  // check if the index is over the half of the list
  bool over_half = index <= self->length / 2;

  // create a cursor node for iteration, if the index is smaller then the
  // half of the list, then start from 0, otherwise start from the tail
  struct Node* cursor = over_half ? self->head : self->tail;

  if (over_half) {
    // step through the list until the desired index is reached
    for (int i = 0; i < index; ++i) {
      cursor = cursor->next;
    }
    return cursor;
  }

  // step through the list until the desired index is reached
  for (int i = self->length - 1; i > index; --i) {
    cursor = cursor->prev;
  }

  return cursor;
}
