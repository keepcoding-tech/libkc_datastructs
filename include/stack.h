// open source c library
// ==================================
//
// stack.h
//
// Daniel Tanase
// 26/06/2023

/*
 * A stack is a fundamental data structure that follows the Last-In-First-Out 
 * (LIFO) principle. It functions as a container where elements can be inserted
 * and removed from the top only. A stack typically consists of a fixed-size 
 * array or a linked list implementation. Operations such as push (insertion) 
 * and pop (removal) are used to manipulate the stack.
 *
 * Push adds an element to the top of the stack, while pop removes the element 
 * from the top. The stack allows for efficient access to the most recently 
 * added elements and is commonly used in scenarios like function calls, 
 * expression evaluation, and backtracking algorithms.
 */

#ifndef STACK_H
#define STACK_H

#include "vector.h"

#include <stdio.h>

struct Stack {
  // a reference to the embedded Vector
  struct Vector* vector;

  // removes the last item in the vector
  void (*pop)(struct Stack* self);

  // adds an item to the end of the vector
  void (*push)(struct Stack* self, void* data, size_t size);
};

// the constructor should be used to create Stack
struct Stack* new_stack();

// the destructor should be used to destroy a Stack
void destroy_stack(struct Stack* stack);

#endif /* STACK_H */
