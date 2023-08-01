// This file is part of keepcoding
// ==================================
//
// node.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/kclog/kclog.h"
#include "../include/node.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// The constructor is used to create new instances of nodes.
struct Node* node_constructor(void* data, size_t size) {
  // create a new instance of console_log for loggining
  struct ConsoleLog* log = new_console_log();

  if (size < 1) {
    log->log_warning("UNDERFLOW", "The data type's size goes below its "
        "minimum representable value.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  // create a Node instance to be returned
  // and allocate space for the data
  struct Node* new_node = malloc(sizeof(struct Node));
  new_node->data = malloc(size);

  if (new_node->data == NULL) {
    log->log_warning("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  // destroy the console log
  destroy_console_log(log);

  // copy the block of memory
  memcpy(new_node->data, data, size);

  // initialize the pointers
  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

// The destructor removes a node by freeing the node's data and its node.
void node_destructor(struct Node* node) {
  // destroy node only if is not dereferenced
  if (node == NULL) {
    struct ConsoleLog* log = new_console_log();
    log->log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  free(node->data);
  free(node);
}
