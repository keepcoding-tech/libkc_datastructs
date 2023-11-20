// This file is part of libkc_datastructs
// ==================================
//
// list.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/exceptions.h"
#include "../include/list.h"

#include <stdlib.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static void erase_all_nodes(struct List* self);
static void erase_first_node(struct List* self);
static void erase_last_node(struct List* self);
static void erase_node(struct List* self, int index);
static void erase_nodes_by_value(struct List* self, void* value, int (*compare)(const void* a, const void* b));
static struct Node* get_first_node(struct List* self);
static struct Node* get_last_node(struct List* self);
static struct Node* get_node(struct List* self, int index);
static void insert_new_head(struct List* self, void* data, size_t size);
static void insert_new_node(struct List* self, int index, void* data, size_t size);
static void insert_new_tail(struct List* self, void* data, size_t size);
static bool is_list_empty(struct List* self);
static bool search_node(struct List* self, void* value, int (*compare)(const void* a, const void* b));

//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static struct Node* iterate_ll(struct List* list, int index);
static struct Node* iterate_forward_ll(struct Node* head, int index);
static struct Node* iterate_reverse_ll(struct Node* tail, int index);

//---------------------------------------------------------------------------//

struct List* new_list()
{
  struct ConsoleLog* logger = new_console_log(err, log_err, __FILE__);

  // create a List instance to be returned
  struct List* new_list = malloc(sizeof(struct List));

  // confirm that there is memory to allocate
  if (new_list == NULL)
  {
    logger->error(logger, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    destroy_console_log(logger);

    // free the instance and exit
    free(new_list);
    exit(1);
  }

  // initialize the structure members fields
  new_list->head   = NULL;
  new_list->tail   = NULL;
  new_list->length = 0;
  new_list->log    = logger;

  // assigns the public member methods
  new_list->back       = get_last_node;
  new_list->clear      = erase_all_nodes;
  new_list->empty      = is_list_empty;
  new_list->erase      = erase_node;
  new_list->front      = get_first_node;
  new_list->get        = get_node;
  new_list->insert     = insert_new_node;
  new_list->pop_back   = erase_last_node;
  new_list->pop_front  = erase_first_node;
  new_list->push_back  = insert_new_tail;
  new_list->push_front = insert_new_head;
  new_list->remove     = erase_nodes_by_value;
  new_list->search     = search_node;

  return new_list;
}

//---------------------------------------------------------------------------//

void destroy_list(struct List* list) 
{
  // if the list reference is NULL, do nothing
  if (list == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  erase_all_nodes(list);
  free(list);
}

//---------------------------------------------------------------------------//

void erase_all_nodes(struct List* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  // start iterating from the head
  struct Node* cursor = self->head;
  while (cursor != NULL)
  {
    struct Node* next = cursor->next;
    node_destructor(cursor);
    cursor = next;
  }

  // reset the head, tail and size
  self->head = NULL;
  self->tail = NULL;
  self->length = 0;
}

//---------------------------------------------------------------------------//

void erase_first_node(struct List* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  struct Node* old_head = self->head;

  // check if this is alos the last node
  if (old_head->next == NULL)
  {
    self->head = NULL;
    self->tail = NULL;
  }
  else
  {
    self->head = old_head->next;
    self->head->prev = NULL;
  }

  node_destructor(old_head);
  --self->length;
}

//---------------------------------------------------------------------------//

void erase_last_node(struct List* self) 
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  struct Node* old_tail = self->tail;

  // check if this is alos the last node
  if (old_tail->prev == NULL)
  {
    self->tail = NULL;
    self->head = NULL;
  }
  else 
  {
    self->tail = old_tail->prev;
    self->tail->next = NULL;
  }

  node_destructor(old_tail);
  --self->length;
}

//---------------------------------------------------------------------------//

void erase_node(struct List* self, int index)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    // log the warning to the console
    self->log->warning(self->log, KC_ERROR_INDEX_OUT_OF_BOUNDS, __LINE__, __func__);

    return;
  }

  // check if the item being removed is the head
  if (index == 0)
  {
    erase_first_node(self);
    return;
  }

  // check if the item being removed is the tail
  if (index == self->length - 1)
  {
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

//---------------------------------------------------------------------------//

void erase_nodes_by_value(struct List* self, void* value,
    int (*compare)(const void* a, const void* b))
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  // start from the head
  struct Node* cursor = self->head;
  size_t index = 0;

  // search the node by value
  while (cursor != NULL) 
  {
    if (compare(cursor->data, value) == 0)
    {
      // erase the head
      if (index == 0)
      {
        cursor = cursor->next;
        erase_first_node(self);
        continue;
      }

      // erase the tail
      if (index == self->length - 1)
      {
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

//---------------------------------------------------------------------------//

struct Node* get_first_node(struct List* self) 
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  return self->head;
}

//---------------------------------------------------------------------------//

struct Node* get_last_node(struct List* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  return self->tail;
}

//---------------------------------------------------------------------------//

struct Node* get_node(struct List* self, int index) 
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    // log the warning to the console
    self->log->warning(self->log, KC_ERROR_INDEX_OUT_OF_BOUNDS, __LINE__, __func__);

    return NULL;
  }

  return iterate_ll(self, index);
}

//---------------------------------------------------------------------------//

void insert_new_head(struct List* self, void* data, size_t size)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  insert_new_node(self, 0, data, size);
}

//---------------------------------------------------------------------------//

void insert_new_node(struct List* self, int index, void* data, size_t size)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  // confirm the user has specified a valid index
  if (index < 0 || index > self->length)
  {
    // log the warning to the console
    self->log->warning(self->log, KC_ERROR_INDEX_OUT_OF_BOUNDS, __LINE__, __func__);

    return;
  }

  // create a new node to be inserted
  struct Node* new_node = node_constructor(data, size);

  // if the node is NULL, don't make the insertion
  if (new_node == NULL) 
  {
    return /* an error has already been displayed */;
  }

  // check if this node will be the new head
  if (index == 0)
  {
    new_node->next = self->head;
    self->head = new_node;

    // if length is less than 1 then head is also tail
    if (self->length == 0)
    {
      self->tail = new_node;
    }

    ++self->length;
    return;
  }

  // find the item in the list immediately before the desired index
  struct Node* cursor = iterate_ll(self, index - 1);

  if (cursor == NULL) 
  {
    return /* an error has already been displayed */;
  }

  new_node->next = cursor->next;
  new_node->prev = cursor;
  cursor->next = new_node;

  // the "prev" of the third node must point to the new node
  if (new_node->next) 
  {
    new_node->next->prev = new_node;
  }

  // check if this node will be the new tail
  if (index == self->length)
  {
    self->tail = new_node;
  }

  // increment the list length
  ++self->length;
}

//---------------------------------------------------------------------------//

void insert_new_tail(struct List* self, void* data, size_t size) 
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  insert_new_node(self, (int)self->length, data, size);
}

//---------------------------------------------------------------------------//

bool is_list_empty(struct List* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  return self->length == 0 && self->head == NULL && self->tail == NULL;
}

//---------------------------------------------------------------------------//

bool search_node(struct List* self, void* value,
    int (*compare)(const void* a, const void* b))
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  // create a new node instance
  struct Node* node = self->head;

  // search the node by value
  while (node != NULL && compare(node->data, value) != 0)
  {
    node = node->next;
  }

  return node != NULL;
}

//---------------------------------------------------------------------------//

struct Node* iterate_ll(struct List* self, int index)
{
  // if the list reference is NULL, do nothing
  if (self == NULL || self->head == NULL || self->tail == NULL)
  {
    log_error(err[KC_ERROR_NULL_REFERENCE], log_err[KC_ERROR_NULL_REFERENCE],
        __FILE__, __LINE__, __func__);

    exit(1);
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    // log the warning to the console
    self->log->warning(self->log, KC_ERROR_INDEX_OUT_OF_BOUNDS, __LINE__, __func__);

    return NULL;
  }

  // check if the index is over the half of the list length, if the index is
  // smaller, then start from the head, otherwise start from the tail
  struct Node* node = index <= self->length / 2 ?
      iterate_forward_ll(self->head, index) :
      iterate_reverse_ll(self->tail, (int)(self->length - 1) - index);

  return node;
}

//---------------------------------------------------------------------------//

struct Node* iterate_forward_ll(struct Node* head, int index)
{
  struct Node* cursor = head;
  for (int i = 0; i < index; ++i)
  {
    cursor = cursor->next;
  }
  return cursor;
}

//---------------------------------------------------------------------------//

struct Node* iterate_reverse_ll(struct Node* tail, int index)
{
  struct Node* cursor = tail;
  for (int i = 0; i < index; ++i)
  {
    cursor = cursor->prev;
  }
  return cursor;
}

//---------------------------------------------------------------------------//

