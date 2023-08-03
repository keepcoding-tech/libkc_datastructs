// This file is part of libkc_datastructs
// ==================================
//
// list.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/kclog/kclog.h"
#include "../include/queue.h"

#include <stdlib.h>

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
size_t get_list_length_queue(struct Queue* self);
void* get_next_item_queue(struct Queue* self);
void insert_next_item_queue(struct Queue* self, void* data, size_t size);
void remove_next_item_queue(struct Queue* self);

// MARK: PRIVATE MEMBER METHODS PROTOTYPES
bool check_queue_reference(struct Queue* queue);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor is used to create new instances of queue.
struct Queue* new_queue() {
  // create a Queue instance to be returned
  struct Queue* new_queue = malloc(sizeof(struct Queue));

  // confirm that there is memory to allocate
  if (new_queue == NULL) {
    struct ConsoleLog* log = new_console_log();
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);

    // free the instance and exit
    free(new_queue);
    exit(1);
  }

  // instantiate the queue's List via the constructor
  new_queue->list = new_list();

  // assigns the public member methods
  new_queue->length = get_list_length_queue;
  new_queue->peek = get_next_item_queue;
  new_queue->pop = remove_next_item_queue;
  new_queue->push = insert_next_item_queue;

  return new_queue;
}

// The destructor removes all the nodes by calling the linked list destructor.
void destroy_queue(struct Queue* queue) {
  // if the queue reference is NULL, do nothing
  if (check_queue_reference(queue) == false) return;

  destroy_list(queue->list);
  free(queue);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function returns the length of the list.
size_t get_list_length_queue(struct Queue* self) {
  // if the queue reference is NULL, do nothing
  if (check_queue_reference(self) == false) return 1;

  return self->list->length;
}

// This function returns the data from the first item in the chain.
void* get_next_item_queue(struct Queue* self) {
  // if the queue reference is NULL, do nothing
  if (check_queue_reference(self) == false) return NULL;

  struct Node* next_item = self->list->front(self->list);

  // check if the head of the list exists
  if (next_item  != NULL) {
    return next_item->data;
  }

  // return null if non-existing
  return NULL;
}

// This function adds an item to the end of the list.
void insert_next_item_queue(struct Queue *self, void *data, size_t size) {
  // if the queue reference is NULL, do nothing
  if (check_queue_reference(self) == false) return;

  self->list->push_back(self->list, data, size);
}

// This function removes the first item in the chain.
void remove_next_item_queue(struct Queue *self) {
  // if the queue reference is NULL, do nothing
  if (check_queue_reference(self) == false) return;

  self->list->pop_front(self->list);
}

// MARK: PRIVATE MEMBER METHODS DEFINITIONS

// This function will check if the queue instance is not dereferenced.
bool check_queue_reference(struct Queue* queue) {
  if (queue == NULL) {
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

