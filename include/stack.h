// This file is part of libkc_datastructs
// ==================================
//
// stack.h
//
// Copyright (c) 2023 Daniel Tanase
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

#ifndef STACK_H
#define STACK_H

#include "vector.h"

#include <stdio.h>

struct Stack
{
  // a reference to the embedded Vector
  struct Vector* vector;

  // returns the length of the vector
  size_t (*length)(struct Stack* self);

  // removes the last item in the vector
  void (*pop)(struct Stack* self);

  // adds an item to the end of the vector
  void (*push)(struct Stack* self, void* data, size_t size);

  // returns the top element (last element in the vector)
  void* (*top)(struct Stack* self);
};

// the constructor should be used to create Stack
struct Stack* new_stack();

// the destructor should be used to destroy a Stack
void destroy_stack(struct Stack* stack);

#endif /* STACK_H */
