// This file is part of libkc_datastructs
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

#include "../deps/libkc/logger/logger.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct List 
{
  struct Node* head;
  struct Node* tail;

  size_t length;

  struct ConsoleLog* log;

  struct Node* (*back)        (struct List* self);
  void         (*clear)       (struct List* self);
  bool         (*empty)       (struct List* self);
  void         (*erase)       (struct List* self, int index);
  struct Node* (*front)       (struct List* self);
  struct Node* (*get)         (struct List* self, int index);
  void         (*insert)      (struct List* self, int index, void* data, size_t size);
  void         (*pop_back)    (struct List* self);
  void         (*pop_front)   (struct List* self);
  void         (*push_back)   (struct List* self, void* data, size_t size);
  void         (*push_front)  (struct List* self, void* data, size_t size);
  void         (*remove)      (struct List* self, void* value, int (*compare)(const void* a, const void* b));
  bool         (*search)      (struct List* self, void* value, int (*compare)(const void* a, const void* b));
};

//---------------------------------------------------------------------------//

struct List* new_list      ();
void         destroy_list  (struct List *list);

//---------------------------------------------------------------------------//

// use this macro to define any type of primitive data comparison function
#define COMPARE_LIST(type, function_name)           \
  int function_name(const void* a, const void* b)   \
  {                                                 \
    if (*(type*)a < *(type*)b)                      \
    {                                               \
      return -1;                                    \
    }                                               \
    if (*(type*)a > *(type*)b)                      \
    {                                               \
      return 1;                                     \
    }                                               \
    return 0;                                       \
  }

#endif /* LIST_H */
