// This file is part of keepcoding_core
// ==================================
//
// stack.h
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * A stack is a fundamental data structure that follows the Last-In-First-Out
 * (LIFO) principle. It functions as a container where elements can be inserted
 * and removed from the top only. Operations such as push (insertion)
 * and pop (removal) are used to manipulate the stack.
 *
 * Push adds an element to the top of the stack, while pop removes the element
 * from the top. The stack allows for efficient access to the most recently
 * added elements and is commonly used in scenarios like function calls,
 * expression evaluation, and backtracking algorithms.
 *
 * To create and destroy instances of the Stack struct, it is recommended
 * to use the constructor and destructor functions.
 *
 * It's important to note that when using member functions, a reference to the
 * Stack instance needs to be passed, similar to how "self" is passed to
 * class member functions in Python. This allows for accessing and manipulating
 * the Stack object's data and behavior.
 */

#ifndef KC_STACK_T_H
#define KC_STACK_T_H

#include "../system/logger.h"

#include "vector.h"

#include <stdio.h>

//---------------------------------------------------------------------------//

#define KC_STACK_LOG_PATH  "build/log/stack.log"

//---------------------------------------------------------------------------//

struct kc_stack_t
{
  struct kc_vector_t* _vector;
  struct kc_logger_t* _logger;

  int (*length)  (struct kc_stack_t* self, size_t* length);
  int (*pop)     (struct kc_stack_t* self);
  int (*push)    (struct kc_stack_t* self, void* data, size_t size);
  int (*top)     (struct kc_stack_t* self, void** top);
};

struct kc_stack_t* new_stack      ();
void               destroy_stack  (struct kc_stack_t* stack);

//---------------------------------------------------------------------------//

#endif /* KC_STACK_T_H */
