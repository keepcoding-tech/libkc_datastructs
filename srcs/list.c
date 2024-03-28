// This file is part of keepcoding_core
// ==================================
//
// list.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../../hdrs/datastructs/list.h"
#include "../../hdrs/common.h"

#include <stdlib.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static int erase_all_nodes       (struct kc_list_t* self);
static int erase_first_node      (struct kc_list_t* self);
static int erase_last_node       (struct kc_list_t* self);
static int erase_node            (struct kc_list_t* self, int index);
static int erase_nodes_by_value  (struct kc_list_t* self, void* value, int (*compare)(const void* a, const void* b));
static int get_first_node        (struct kc_list_t* self, struct kc_node_t** front_node);
static int get_last_node         (struct kc_list_t* self, struct kc_node_t** back_node);
static int get_node              (struct kc_list_t* self, int index, struct kc_node_t** node);
static int insert_new_head       (struct kc_list_t* self, void* data, size_t size);
static int insert_new_node       (struct kc_list_t* self, int index, void* data, size_t size);
static int insert_new_tail       (struct kc_list_t* self, void* data, size_t size);
static int is_list_empty         (struct kc_list_t* self, bool* is_empty);
static int search_node           (struct kc_list_t* self, void* value, int (*compare)(const void* a, const void* b), bool* exists);


//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static struct kc_node_t* _iterate_ll          (struct kc_list_t* list, int index);
static struct kc_node_t* _iterate_forward_ll  (struct kc_node_t* head, int index);
static struct kc_node_t* _iterate_reverse_ll  (struct kc_node_t* tail, int index);

//---------------------------------------------------------------------------//

struct kc_list_t* new_list()
{
  // create a List instance to be returned
  struct kc_list_t* new_list = malloc(sizeof(struct kc_list_t));

  // confirm that there is memory to allocate
  if (new_list == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return NULL;
  }

  new_list->_logger = new_logger(KC_LIST_LOG_PATH);

  // confirm that there is memory to allocate
  if (new_list->_logger == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    // free the list instance
    free(new_list);

    return NULL;
  }

  // initialize the structure members fields
  new_list->_head   = NULL;
  new_list->_tail   = NULL;
  new_list->length  = 0;

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

void destroy_list(struct kc_list_t* list)
{
  // if the list reference is NULL, abort the application
  if (list == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return;
  }

  destroy_logger(list->_logger);

  erase_all_nodes(list);
  free(list);
}

//---------------------------------------------------------------------------//

int erase_all_nodes(struct kc_list_t* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // start iterating from the head
  struct kc_node_t* cursor = self->_head;
  while (cursor != NULL)
  {
    struct kc_node_t* next = cursor->next;
    node_destructor(cursor);
    cursor = next;
  }

  // reset the head, tail and size
  self->_head = NULL;
  self->_tail = NULL;
  self->length = 0;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int erase_first_node(struct kc_list_t* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  struct kc_node_t* old_head = self->_head;

  // check if this is alos the last node
  if (old_head->next == NULL)
  {
    self->_head = NULL;
    self->_tail = NULL;
  }
  else
  {
    self->_head = old_head->next;
    self->_head->prev = NULL;
  }

  node_destructor(old_head);
  --self->length;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int erase_last_node(struct kc_list_t* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  struct kc_node_t* old_tail = self->_tail;

  // check if this is alos the last node
  if (old_tail->prev == NULL)
  {
    self->_tail = NULL;
    self->_head = NULL;
  }
  else
  {
    self->_tail = old_tail->prev;
    self->_tail->next = NULL;
  }

  node_destructor(old_tail);
  --self->length;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int erase_node(struct kc_list_t* self, int index)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, KC_INDEX_OUT_OF_BOUNDS,
        __FILE__, __LINE__, __func__);

    return KC_INDEX_OUT_OF_BOUNDS;
  }

  // check if the item being removed is the head
  if (index == 0)
  {
    return erase_first_node(self);
  }

  // check if the item being removed is the tail
  if (index == self->length - 1)
  {
    return erase_last_node(self);
  }

  // find the node in the list before the one that is going to be removed
  struct kc_node_t* current = _iterate_ll(self, index - 1);

  // use the node returned to define the node to be removed
  struct kc_node_t *node_to_remove = current->next;
  current->next = node_to_remove->next;
  current->next->prev = current;

  node_destructor(node_to_remove);

  --self->length;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int erase_nodes_by_value(struct kc_list_t* self, void* value, int (*compare)(const void* a, const void* b))
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // start from the head
  struct kc_node_t* cursor = self->_head;
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

        int ret = erase_first_node(self);
        if (ret != KC_SUCCESS)
        {
          return ret;
        }

        continue;
      }

      // erase the tail
      if (index == self->length - 1)
      {
        int ret = erase_last_node(self);
        if (ret != KC_SUCCESS)
        {
          return ret;
        }

        break;
      }

      // use the node cursor to define the node to be removed
      struct kc_node_t *node_to_remove = cursor;
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

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int get_first_node(struct kc_list_t* self, struct kc_node_t** first_node)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  (*first_node) = self->_head;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int get_last_node(struct kc_list_t* self, struct kc_node_t** last_node)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // if length is less than 1 then head is also tail
  if (self->length == 0)
  {
    (*last_node) = self->_head;
  }
  else
  {
    (*last_node) = self->_tail;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int get_node(struct kc_list_t* self, int index, struct kc_node_t** node)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    // log the warning to the console
    self->_logger->log(self->_logger, KC_WARNING_LOG, KC_INDEX_OUT_OF_BOUNDS,
        __FILE__, __LINE__, __func__);

    return KC_INDEX_OUT_OF_BOUNDS;
  }

  (*node) = _iterate_ll(self, index);

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int insert_new_head(struct kc_list_t* self, void* data, size_t size)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  return insert_new_node(self, 0, data, size);
}

//---------------------------------------------------------------------------//

int insert_new_node(struct kc_list_t* self, int index, void* data, size_t size)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index > self->length)
  {
    // log the warning to the console
    self->_logger->log(self->_logger, KC_WARNING_LOG, KC_INDEX_OUT_OF_BOUNDS,
        __FILE__, __LINE__, __func__);

    return KC_INDEX_OUT_OF_BOUNDS;
  }

  // create a new node to be inserted
  struct kc_node_t* new_node = node_constructor(data, size);

  // if the node is NULL, don't make the insertion
  if (new_node == NULL)
  {
    return KC_INVALID; /* an error has already been displayed */
  }

  // check if this node will be the new head
  if (index == 0)
  {
    new_node->next = self->_head;
    self->_head = new_node;

    // if length is less than 1 then head is also tail
    if (self->length == 0)
    {
      self->_tail = new_node;
    }

    ++self->length;

    return KC_SUCCESS;
  }

  // find the item in the list immediately before the desired index
  struct kc_node_t* cursor = _iterate_ll(self, index - 1);

  if (cursor == NULL)
  {
    return KC_NULL_REFERENCE; /* an error has already been displayed */
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
    self->_tail = new_node;
  }

  // increment the list length
  ++self->length;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int insert_new_tail(struct kc_list_t* self, void* data, size_t size)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  return insert_new_node(self, (int)self->length, data, size);
}

//---------------------------------------------------------------------------//

int is_list_empty(struct kc_list_t* self, bool* is_empty)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  if (self->length == 0 && self->_head == NULL && self->_tail == NULL)
  {
    (*is_empty) = true;
  }
  else
  {
    (*is_empty) = false;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int search_node(struct kc_list_t* self, void* value,
    int (*compare)(const void* a, const void* b), bool* exists)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // create a new node instance
  struct kc_node_t* node = self->_head;

  // search the node by value
  while (node != NULL && compare(node->data, value) != 0)
  {
    node = node->next;
  }

  if (node != NULL)
  {
    (*exists) = true;
  }
  else
  {
    (*exists) = false;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

struct kc_node_t* _iterate_ll(struct kc_list_t* self, int index)
{
  // if the list reference is NULL, do nothing
  if (self == NULL || self->_head == NULL || self->_tail == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return NULL;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    // log the warning to the console
    self->_logger->log(self->_logger, KC_WARNING_LOG, KC_INDEX_OUT_OF_BOUNDS,
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  // check if the index is over the half of the list length, if the index is
  // smaller, then start from the head, otherwise start from the tail
  struct kc_node_t* node = index <= self->length / 2 ?
      _iterate_forward_ll(self->_head, index) :
      _iterate_reverse_ll(self->_tail, (int)(self->length - 1) - index);

  return node;
}

//---------------------------------------------------------------------------//

struct kc_node_t* _iterate_forward_ll(struct kc_node_t* head, int index)
{
  struct kc_node_t* cursor = head;
  for (int i = 0; i < index; ++i)
  {
    cursor = cursor->next;
  }
  return cursor;
}

//---------------------------------------------------------------------------//

struct kc_node_t* _iterate_reverse_ll(struct kc_node_t* tail, int index)
{
  struct kc_node_t* cursor = tail;
  for (int i = 0; i < index; ++i)
  {
    cursor = cursor->prev;
  }
  return cursor;
}

//---------------------------------------------------------------------------//

