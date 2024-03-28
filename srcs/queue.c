// This file is part of keepcoding_core
// ==================================
//
// queue.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../../hdrs/datastructs/queue.h"
#include "../../hdrs/common.h"

#include <stdlib.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static int get_list_length_queue   (struct kc_queue_t* self, size_t* length);
static int get_next_item_queue     (struct kc_queue_t* self, void** peek);
static int insert_next_item_queue  (struct kc_queue_t* self, void* data, size_t size);
static int remove_next_item_queue  (struct kc_queue_t* self);

//---------------------------------------------------------------------------//

struct kc_queue_t* new_queue()
{
  // create a Queue instance to be returned
  struct kc_queue_t* new_queue = malloc(sizeof(struct kc_queue_t));

  // confirm that there is memory to allocate
  if (new_queue == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return NULL;
  }

  // instantiate the queue's List via the constructor
  new_queue->_list = new_list();

  if (new_queue->_list == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    // free the set instance
    free(new_queue);

    return NULL;
  }

  new_queue->_logger = new_logger(KC_QUEUE_LOG_PATH);

  if (new_queue->_logger == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    // free the set instances
    destroy_list(new_queue->_list);
    free(new_queue);

    return NULL;
  }

  // assigns the public member methods
  new_queue->length = get_list_length_queue;
  new_queue->peek   = get_next_item_queue;
  new_queue->pop    = remove_next_item_queue;
  new_queue->push   = insert_next_item_queue;

  return new_queue;
}

//---------------------------------------------------------------------------//

void destroy_queue(struct kc_queue_t* queue)
{
  // if the list reference is NULL, do nothing
  if (queue == NULL)
  {
    // log the warning to the console
    log_error(KC_NULL_REFERENCE_LOG);

    return;
  }

  destroy_logger(queue->_logger);
  destroy_list(queue->_list);
  free(queue);
}

//---------------------------------------------------------------------------//

int get_list_length_queue(struct kc_queue_t* self, size_t* length)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  (*length) = self->_list->length;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int get_next_item_queue(struct kc_queue_t* self, void** peek)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  struct kc_node_t* next_item = NULL;
  int ret = self->_list->front(self->_list, &next_item);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  // check if the head of the list exists
  if (next_item != NULL && next_item->data != NULL)
  {
    (*peek) = next_item->data;

    return KC_SUCCESS;
  }

  return KC_EMPTY_STRUCTURE;
}

//---------------------------------------------------------------------------//

int insert_next_item_queue(struct kc_queue_t *self, void *data, size_t size)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  int ret = self->_list->push_back(self->_list, data, size);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int remove_next_item_queue(struct kc_queue_t *self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  int ret = self->_list->pop_front(self->_list);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

