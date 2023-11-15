// This file is part of libkc_datastructs
// ==================================
//
// node.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc_logger/logger.h"
#include "../include/node.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------//

struct Node* node_constructor(void* data, size_t size) 
{
  if (size < 1) {
    log_warning("UNDERFLOW", "The data type's size goes below its "
        "minimum representable value.", __FILE__, __LINE__, __func__);
    return NULL;
  }

  // create a Node instance to be returned
  // and allocate space for the data
  struct Node* new_node = malloc(sizeof(struct Node));

  if (new_node == NULL)
  {
    log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);

    // free the instances and exit
    exit(1);
  }

  new_node->data = malloc(size);

  if (new_node->data == NULL)
  {
    log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);

    // free the instances and exit
    free(new_node->data);
    free(new_node);
    exit(1);
  }

  // copy the block of memory
  memcpy(new_node->data, data, size);

  // initialize the pointers
  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

//---------------------------------------------------------------------------//

void node_destructor(struct Node* node)
{
  // destroy node only if is not dereferenced
  if (node == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);
    return;
  }

  free(node->data);
  free(node);
}

//---------------------------------------------------------------------------//
