// This file is part of libkc_datastructs
// ==================================
//
// queue.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/exceptions.h"
#include "../include/queue.h"

#include <stdlib.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static size_t get_list_length_queue(struct Queue* self);
static void* get_next_item_queue(struct Queue* self);
static void insert_next_item_queue(struct Queue* self, void* data, size_t size);
static void remove_next_item_queue(struct Queue* self);

//---------------------------------------------------------------------------//

struct Queue* new_queue()
{
  struct ConsoleLog* logger = new_console_log(err, log_err, __FILE__);

  // create a Queue instance to be returned
  struct Queue* new_queue = malloc(sizeof(struct Queue));

  // confirm that there is memory to allocate
  if (new_queue == NULL) 
  {
    logger->error(logger, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    destroy_console_log(logger);

    // free the instance and exit
    free(new_queue);
    exit(1);
  }

  // instantiate the queue's List via the constructor
  new_queue->list = new_list();
  new_queue->log  = logger;

  // assigns the public member methods
  new_queue->length = get_list_length_queue;
  new_queue->peek   = get_next_item_queue;
  new_queue->pop    = remove_next_item_queue;
  new_queue->push   = insert_next_item_queue;

  return new_queue;
}

//---------------------------------------------------------------------------//

void destroy_queue(struct Queue* queue)
{
  // if the list reference is NULL, do nothing
  if (queue == NULL)
  {
    // log the warning to the console
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  destroy_list(queue->list);
  free(queue);
}

//---------------------------------------------------------------------------//

size_t get_list_length_queue(struct Queue* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    // log the warning to the console
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return 1;
  }

  return self->list->length;
}

//---------------------------------------------------------------------------//

void* get_next_item_queue(struct Queue* self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    // log the warning to the console
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  struct Node* next_item = self->list->front(self->list);

  // check if the head of the list exists
  if (next_item  != NULL)
  {
    return next_item->data;
  }

  // return null if non-existing
  return NULL;
}

//---------------------------------------------------------------------------//

void insert_next_item_queue(struct Queue *self, void *data, size_t size)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    // log the warning to the console
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  self->list->push_back(self->list, data, size);
}

//---------------------------------------------------------------------------//

void remove_next_item_queue(struct Queue *self)
{
  // if the list reference is NULL, do nothing
  if (self == NULL)
  {
    // log the warning to the console
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  self->list->pop_front(self->list);
}

//---------------------------------------------------------------------------//

