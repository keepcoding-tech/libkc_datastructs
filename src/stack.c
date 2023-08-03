// This file is part of keepcoding
// ==================================
//
// stack.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/kclog/kclog.h"
#include "../include/stack.h"

#include <stdlib.h>

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
void* get_top_item_stack(struct Stack* self);
size_t get_vector_length_stack(struct Stack* self);
void insert_top_item_stack(struct Stack* self, void* data, size_t size);
void remove_top_item_stack(struct Stack* self);

// MARK: PRIVATE MEMBER METHODS PROTOTYPES
bool check_stack_reference(struct Stack* stack);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor is used to create new instances of stack.
struct Stack* new_stack() {
  // create a Stack instance to be returned
  struct Stack* new_stack = malloc(sizeof(struct Stack));

  // confirm that there is memory to allocate
  if (new_stack == NULL) {
    struct ConsoleLog* log = new_console_log();
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);

    // free the instance and exit
    free(new_stack);
    exit(1);
  }

  // instantiate the stack's Vector via the constructor
  new_stack->vector = new_vector();

  // assigns the public member methods
  new_stack->length = get_vector_length_stack;
  new_stack->pop = remove_top_item_stack;
  new_stack->push = insert_top_item_stack;
  new_stack->top = get_top_item_stack;

  return new_stack;
}

// The destructor removes all the items by calling the Vector destructor.
void destroy_stack(struct Stack* stack) {
  // if the stack reference is NULL, do nothing
  if (check_stack_reference(stack) == false) return;

  destroy_vector(stack->vector);
  free(stack);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function returns the data from the last item in the array.
void* get_top_item_stack(struct Stack* self) {
  // if the stack reference is NULL, do nothing
  if (check_stack_reference(self) == false) return NULL;

  return self->vector->back(self->vector);
}

// This function returns the length of the vector.
size_t get_vector_length_stack(struct Stack* self) {
  // if the stack reference is NULL, do nothing
  if (check_stack_reference(self) == false) return 1;

  return self->vector->length;
}

// This function adds an item to the end of the vector.
void insert_top_item_stack(struct Stack* self, void* data, size_t size) {
  // if the stack reference is NULL, do nothing
  if (check_stack_reference(self) == false) return;

  // utilize the push_back from Vector with enforced parameters
  self->vector->push_back(self->vector, data, size);
}

// This function removes the last item in the vector.
void remove_top_item_stack(struct Stack* self) {
  // if the stack reference is NULL, do nothing
  if (check_stack_reference(self) == false) return;

  // utilize the erase from Vector with enforced parameters
  self->vector->pop_back(self->vector);
}

// MARK: PRIVATE MEMBER METHODS DEFINITIONS

// This function will check if the stack instance is not dereferenced.
bool check_stack_reference(struct Stack* stack) {
  if (stack == NULL) {
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
