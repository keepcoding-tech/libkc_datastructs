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

#include "../deps/libkc/logger/logger.h"
#include "vector.h"

#include <stdio.h>

struct Stack
{
  struct Vector* vector;

  struct ConsoleLog* log;

  size_t (*length)  (struct Stack* self);
  void   (*pop)     (struct Stack* self);
  void   (*push)    (struct Stack* self, void* data, size_t size);
  void*  (*top)     (struct Stack* self);
};

struct Stack* new_stack      ();
void          destroy_stack  (struct Stack* stack);

#endif /* STACK_H */
