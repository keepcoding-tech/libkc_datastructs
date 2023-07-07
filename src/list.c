#include "../include/list.h"

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
// void erase_all_nodes(struct List* self);
// void erase_first_node(struct List* self);
// void erase_last_node(struct List* self);
void erase_node(struct List* self, size_t index);
// void erase_nodes_by_value(struct List* self, void* data,
//     bool (*compare)(void* data_one, void* data_two));
// struct Node* get_first_node(struct List* self);
// struct Node* get_last_node(struct List* self);
struct Node* get_node(struct List* self, int index);
// void insert_new_head(struct List* self, void* data, size_t size);
void insert_new_node(struct List* self, int index, void* data, size_t size);
// void insert_new_tail(struct List* self, void* data, size_t size);
bool is_list_empty(struct List* self);
bool search_node(struct List* self, void* query,
    bool (*compare)(void* data_one, void* data_two));

// MARK: PRIVATE MEMBER METHODS PROTOTYPES
void destroy_node_ll(struct Node* node_to_destroy);
struct Node* iterate_ll(struct List* self, int index);


// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor is used to create new instances of linked list.
struct List* new_list() {
  // create a List instance to be returned
  struct List* new_list = malloc(sizeof(struct List));

  // initialize the structure members fields
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->length = 0;

  // assigns the public member methods
  // new_list->back = get_last_node;
  // new_list->clear = erase_all_nodes;
  new_list->empty = is_list_empty;
  new_list->erase = erase_node;
  // new_list->front = get_first_node;
  new_list->get = get_node;
  new_list->insert = insert_new_node;
  // new_list->pop_back = erase_last_node;
  // new_list->pop_front = erase_first_node;
  // new_list->push_back = insert_new_tail;
  // new_list->push_front = insert_new_head;
  // new_list->remove = erase_nodes_by_value;
  new_list->search = search_node;

  return new_list;
}

// The destructor removes all the nodes by freeing the nodes instances and data.
void destroy_list(struct List* list) {
  // access the linked list length only once
  int list_length = list->length;
  for (int i = 0; i < list_length; ++i) {
    list->erase(list, 0);
  }

  // free the linked list too
  free(list);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function removes from the list a single element (position).
void erase_node(struct List* self, size_t index) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    printf("keepcoding/List ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Index out of bound!\n");
    return;
  }

  // get the "head" of the list
  struct Node* current = self->head;

  // check if the item being removed is the "head"
  if (index == 0) {
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

// This function allows data in the chain to be accessed.
struct Node* get_node(struct List* self, int index) {
  // find the desired node and return its data
  struct Node* node = iterate_ll(self, index);

  if (node) {
    return node;
  }

  // if no node found, return null
  return NULL;
}

// This function adds new items to the chain at a specified location.
void insert_new_node(struct List* self, int index, void* data, size_t size) {
  // create a new node to be inserted
  struct Node* new_node = node_constructor(data, size);

  // if the node is NULL, don't make the insertion
  if (new_node == NULL) {
    return;
  }

  // check if this node will be the new head
  if (index == 0) {
    new_node->next = self->head;
    self->head = new_node;
    ++self->length;
    return;
  }

  // find the item in the list immediately before the desired index
  struct Node* cursor = iterate_ll(self, index - 1);

  new_node->next = cursor->next;
  new_node->prev = cursor;
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

// This function returns whether the list is empty or not.
bool is_list_empty(struct List* self) {
  return self->length == 0 && !self->head;
}

// This function searchs for a specific node by data.
bool search_node(struct List* self, void* query,
    bool (*compare)(void* data_one, void* data_two)) {
  // create a new node instance
  struct Node* node = self->head;

  // search the node by value
  while (node != NULL) {
    if (compare(node->data, query)) {
      return true;
    }
    node = node->next;
  }

  return false;
}

// MARK: PRIVATE MEMBER METHODS DEFINITIONS

// This function removes a node by deallocating it's memory
// address, this simply renames the node destructor function.
void destroy_node_ll(struct Node* node_to_destroy) {
  node_destructor(node_to_destroy);
}

// This function traverses the list from beginning to end.
struct Node* iterate_ll(struct List* self, int index) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    printf("keepcoding/List ... \n");
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
