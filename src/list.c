// This file is part of libkc_datastructs
// ==================================
//
// list.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/kclog/kclog.h"
#include "../include/list.h"

#include <stdlib.h>

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
void erase_all_nodes(struct List* self);
void erase_first_node(struct List* self);
void erase_last_node(struct List* self);
void erase_node(struct List* self, size_t index);
void erase_nodes_by_value(struct List* self, void* value,
    int (*compare)(const void* a, const void* b));
struct Node* get_first_node(struct List* self);
struct Node* get_last_node(struct List* self);
struct Node* get_node(struct List* self, int index);
void insert_new_head(struct List* self, void* data, size_t size);
void insert_new_node(struct List* self, int index, void* data, size_t size);
void insert_new_tail(struct List* self, void* data, size_t size);
bool is_list_empty(struct List* self);
bool search_node(struct List* self, void* value,
    int (*compare)(const void* a, const void* b));

// MARK: PRIVATE MEMBER METHODS PROTOTYPES
bool check_list_reference(struct List* list);
struct Node* iterate_ll(struct List* list, int index);
struct Node* iterate_forward_ll(struct Node* head, int index);
struct Node* iterate_reverse_ll(struct Node* tail, int index);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor is used to create new instances of linked list.
struct List* new_list() {
  // create a List instance to be returned
  struct List* new_list = malloc(sizeof(struct List));

  // confirm that there is memory to allocate
  if (new_list == NULL) {
    struct ConsoleLog* log = new_console_log();
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);

    // free the instance and exit
    free(new_list);
    exit(1);
  }

  // initialize the structure members fields
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->length = 0;

  // assigns the public member methods
  new_list->back = get_last_node;
  new_list->clear = erase_all_nodes;
  new_list->empty = is_list_empty;
  new_list->erase = erase_node;
  new_list->front = get_first_node;
  new_list->get = get_node;
  new_list->insert = insert_new_node;
  new_list->pop_back = erase_last_node;
  new_list->pop_front = erase_first_node;
  new_list->push_back = insert_new_tail;
  new_list->push_front = insert_new_head;
  new_list->remove = erase_nodes_by_value;
  new_list->search = search_node;

  return new_list;
}

// The destructor removes all the nodes by freeing
// the nodes instances and the stored data.
void destroy_list(struct List* list) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(list) == false) return;

  erase_all_nodes(list);
  free(list);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function removes all elements from the list leaving it
// with a size of 0 and reinitializing the head and tail to NULL.
void erase_all_nodes(struct List* self) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return;

  // start iterating from the head
  struct Node* cursor = self->head;
  while (cursor != NULL) {
    struct Node* next = cursor->next;
    node_destructor(cursor);
    cursor = next;
  }

  // reset the head, tail and size
  self->head = NULL;
  self->tail = NULL;
  self->length = 0;
}

// This function removes the last element in
// the list, reducing the size by one.
void erase_first_node(struct List* self) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false || self->head == NULL) return;

  struct Node* old_head = self->head;

  // check if this is alos the last node
  if (old_head->next == NULL) {
    self->head = NULL;
    self->tail = NULL;
  } else {
    self->head = old_head->next;
    self->head->prev = NULL;
  }

  node_destructor(old_head);
  --self->length;
}

// This function removes the first element in
// the list, reducing the size by one.
void erase_last_node(struct List* self) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false || self->tail == NULL) return;

  struct Node* old_tail = self->tail;

  // check if this is alos the last node
  if (old_tail->prev == NULL) {
    self->tail = NULL;
    self->head = NULL;
  } else {
    self->tail = old_tail->prev;
    self->tail->next = NULL;
  }

  node_destructor(old_tail);
  --self->length;
}

// This function removes from the list a single element (position).
void erase_node(struct List* self, size_t index) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return;

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    struct ConsoleLog* log = new_console_log();
    log->log_warning("INDEX_OUT_OF_BOUNDS", "You are trying to access an "
        "element at an invalid index in an array, list, or other indexed "
        "data structure.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // check if the item being removed is the head
  if (index == 0) {
    erase_first_node(self);
    return;
  }

  // check if the item being removed is the tail
  if (index == self->length - 1) {
    erase_last_node(self);
    return;
  }

  // find the node in the list before the one that is going to be removed
  struct Node* current = iterate_ll(self, index - 1);

  // use the node returned to define the node to be removed
  struct Node *node_to_remove = current->next;
  current->next = node_to_remove->next;
  current->next->prev = current;

  node_destructor(node_to_remove);

  --self->length;
}

// This function removes from the list all
// the nodes that compare equal to value.
void erase_nodes_by_value(struct List* self, void* value,
    int (*compare)(const void* a, const void* b)) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return;

  // start from the head
  struct Node* cursor = self->head;
  size_t index = 0;

  // search the node by value
  while (cursor != NULL) {
    if (compare(cursor->data, value) == 0) {
      // erase the head
      if (index == 0) {
        cursor = cursor->next;
        erase_first_node(self);
        continue;
      }

      // erase the tail
      if (index == self->length - 1) {
        erase_last_node(self);
        break;
      }

      // use the node cursor to define the node to be removed
      struct Node *node_to_remove = cursor;
      cursor->prev->next = cursor->next;
      cursor->next->prev = cursor->prev;
      cursor = cursor->next;

      node_destructor(node_to_remove);
      --self->length;
      continue;
    }

    // continue searching
    cursor = cursor->next;
    ++index;
  }
}

// This function returns a reference to the first element in the list.
struct Node* get_first_node(struct List* self) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false || self->head == NULL) return NULL;

  return self->head;
}

// This function returns a reference to the last element in the list.
struct Node* get_last_node(struct List* self) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false || self->tail == NULL) return NULL;

  return self->tail;
}

// This function allows data in the chain to be accessed.
struct Node* get_node(struct List* self, int index) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return NULL;

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    struct ConsoleLog* log = new_console_log();
    log->log_warning("INDEX_OUT_OF_BOUNDS", "You are trying to access an "
        "element at an invalid index in an array, list, or other indexed "
        "data structure.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  return iterate_ll(self, index);
}

// This function adds a new element at the end
// of the list, incrementing the size by one.
void insert_new_head(struct List* self, void* data, size_t size) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return;

  insert_new_node(self, 0, data, size);
}

// This function adds new items to the chain at a specified location.
void insert_new_node(struct List* self, int index, void* data, size_t size) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return;

  // confirm the user has specified a valid index
  if (index < 0 || index > self->length) {
    struct ConsoleLog* log = new_console_log();
    log->log_warning("INDEX_OUT_OF_BOUNDS", "You are trying to access an "
        "element at an invalid index in an array, list, or other indexed "
        "data structure.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // create a new node to be inserted
  struct Node* new_node = node_constructor(data, size);

  // if the node is NULL, don't make the insertion
  if (new_node == NULL) {
    return /* an error has already been displayed */;
  }

  // check if this node will be the new head
  if (index == 0) {
    new_node->next = self->head;
    self->head = new_node;

    // if length is less than 1 then head is also tail
    if (self->length == 0) {
      self->tail = new_node;
    }

    ++self->length;
    return;
  }

  // find the item in the list immediately before the desired index
  struct Node* cursor = iterate_ll(self, index - 1);

  if (cursor == NULL) {
    return /* an error has already been displayed */;
  }

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

// This function adds a new element at the front
// of the list, incrementing the size by one.
void insert_new_tail(struct List* self, void* data, size_t size) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return;

  insert_new_node(self, self->length, data, size);
}

// This function returns whether the list is empty or not.
bool is_list_empty(struct List* self) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return NULL;

  return self->length == 0 && self->head == NULL && self->tail == NULL;
}

// This function searchs for a specific node by data.
bool search_node(struct List* self, void* value,
    int (*compare)(const void* a, const void* b)) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false) return NULL;

  // create a new node instance
  struct Node* node = self->head;

  // search the node by value
  while (node != NULL && compare(node->data, value) != 0) {
    node = node->next;
  }

  return node != NULL;
}

// MARK: PRIVATE MEMBER METHODS DEFINITIONS

// This function will check if the list instance is not dereferenced.
bool check_list_reference(struct List* list) {
  if (list == NULL) {
    // create a new instance of console_log for loggining
    struct ConsoleLog* log = new_console_log();

    // log the warning to the console
    log->log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    // destroy the console log
    destroy_console_log(log);

    return false;
  }

  return true;
}

// This function traverses the list from beginning to end.
struct Node* iterate_ll(struct List* self, int index) {
  // if the list reference is NULL, do nothing
  if (check_list_reference(self) == false ||
      self->head == NULL || self->tail == NULL) {
    return NULL;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    struct ConsoleLog* log = new_console_log();
    log->log_warning("INDEX_OUT_OF_BOUNDS", "You are trying to access an "
        "element at an invalid index in an array, list, or other indexed "
        "data structure.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  // check if the index is over the half of the list length, if the index is
  // smaller, then start from the head, otherwise start from the tail
  struct Node* node = index <= self->length / 2 ?
      iterate_forward_ll(self->head, index) :
      iterate_reverse_ll(self->tail, (self->length - 1) - index);

  return node;
}

// This function traverses the list from beginning to the position specified.
struct Node* iterate_forward_ll(struct Node* head, int index) {
  struct Node* cursor = head;
  for (int i = 0; i < index; ++i) {
    cursor = cursor->next;
  }
  return cursor;
}

// This function traverses the list from end to the position specified.
struct Node* iterate_reverse_ll(struct Node* tail, int index) {
  struct Node* cursor = tail;
  for (int i = 0; i < index; ++i) {
    cursor = cursor->prev;
  }
  return cursor;
}

