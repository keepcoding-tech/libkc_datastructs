// This file is part of keepcoding
// ==================================
//
// list.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * The List struct represents a dynamic implementation of a linked list,
 * consisting of interconnected Nodes. Each Node points to the next and
 * previous nodes in the chain. Unlike static implementations, this List
 * allows for flexible data types and can be resized as needed.
 *
 * The List object simplifies the process of creating and destroying
 * nodes automatically, enabling users to focus on inserting their desired data.
 * To accommodate various data types, node data is stored as void pointers,
 * requiring appropriate casting when accessed.
 *
 * To create and destroy instances of the List struct, it is recommended
 * to use the constructor and destructor functions.
 *
 * It's important to note that when using member functions, a reference to the
 * List instance needs to be passed, similar to how "self" is passed to
 * class member functions in Python. This allows for accessing and manipulating
 * the List object's data and behavior.
 */

#ifndef LIST_H
#define LIST_H

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct List {
  // points to the first and last node in the chain
  struct Node* head;
  struct Node* tail;

  // length refers to the number of nodes in the chain
  size_t length;

  // returns a reference to the last element in the list
  struct Node* (*back)(struct List* self);

  // removes all elements from the list leaving it with a size of 0
  void (*clear)(struct List* self);

  // returns whether the list is empty or not
  bool (*empty)(struct List* self);

  // removes from the list a single element (position)
  void (*erase)(struct List* self, size_t index);

  // returns a reference to the first element in the list
  struct Node* (*front)(struct List* self);

  // allows data in the chain to be accessed
  struct Node* (*get)(struct List* self, int index);

  // adds new items to the chain at a specified location
  void (*insert)(struct List* self, int index, void* data, size_t size);

  // removes the last element in the list, reducing the size by one
  void (*pop_back)(struct List* self);

  // removes the first element in the list, reducing the size by one
  void (*pop_front)(struct List* self);

  // adds a new element at the end of the list, incrementing the size
  void (*push_back)(struct List* self, void* data, size_t size);

  // adds a new element at the front of the list, incrementing the size
  void (*push_front)(struct List* self, void* data, size_t size);

  // removes from the list all the elements that compare equal to value
  void (*remove)(struct List* self, void* value,
      int (*compare)(const void* a, const void* b));

  // search a specified node by value
  bool (*search)(struct List* self, void* value,
      int (*compare)(const void* a, const void* b));
};

// the constructor should be used to create linked lists
struct List* new_list();

// the destructor should be used to destroy linked lists
void destroy_list(struct List *list);

// use this macro to define any type of primitive data comparison function
#define COMPARE_LIST(type, function_name) \
  int function_name(const void* a, const void* b) { \
    if (*(type*)a < *(type*)b) {                    \
      return -1;                                    \
    }                                               \
    if (*(type*)a > *(type*)b) {                    \
      return 1;                                     \
    }                                               \
    return 0;                                       \
  }

#endif /* LIST_H */
