// This file is part of libkc_datastructs
// ==================================
//
// stack.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/exceptions.h"
#include "../include/stack.h"

#include <stdlib.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static void* get_top_item_stack(struct Stack* self);
static size_t get_vector_length_stack(struct Stack* self);
static void insert_top_item_stack(struct Stack* self, void* data, size_t size);
static void remove_top_item_stack(struct Stack* self);

//---------------------------------------------------------------------------//

struct Stack* new_stack()
{
  struct ConsoleLog* logger = new_console_log(err, log_err, __FILE__);

  // create a Stack instance to be returned
  struct Stack* new_stack = malloc(sizeof(struct Stack));

  // confirm that there is memory to allocate
  if (new_stack == NULL)
  {
    logger->error(logger, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    destroy_console_log(logger);

    // free the instance and exit
    free(new_stack);
    exit(1);
  }

  // instantiate the stack's Vector via the constructor
  new_stack->vector = new_vector();
  new_stack->log    = logger;

  // assigns the public member methods
  new_stack->length = get_vector_length_stack;
  new_stack->pop    = remove_top_item_stack;
  new_stack->push   = insert_top_item_stack;
  new_stack->top    = get_top_item_stack;

  return new_stack;
}

//---------------------------------------------------------------------------//

void destroy_stack(struct Stack* stack)
{
  // if the stack reference is NULL, do nothing
  if (stack == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  destroy_vector(stack->vector);
  free(stack);
}

//---------------------------------------------------------------------------//

void* get_top_item_stack(struct Stack* self)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  return self->vector->back(self->vector);
}

//---------------------------------------------------------------------------//

size_t get_vector_length_stack(struct Stack* self)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return 1;
  }

  return self->vector->length;
}

//---------------------------------------------------------------------------//

void insert_top_item_stack(struct Stack* self, void* data, size_t size)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  // utilize the push_back from Vector with enforced parameters
  self->vector->push_back(self->vector, data, size);
}

//---------------------------------------------------------------------------//

void remove_top_item_stack(struct Stack* self)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  // utilize the erase from Vector with enforced parameters
  self->vector->pop_back(self->vector);
}

//---------------------------------------------------------------------------//
