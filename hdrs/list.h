// This file is part of keepcoding_core
// ==================================
//
// list.h
//
// Copyright (c) 2024 Daniel Tanase
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

#ifndef KC_LIST_T_H
#define KC_LIST_T_H

#include "../system/logger.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------//

#define KC_LIST_LOG_PATH  "build/log/list.log"

//---------------------------------------------------------------------------//

struct kc_list_t
{
  struct kc_node_t*   _head;
  struct kc_node_t*   _tail;
  struct kc_logger_t* _logger;

  size_t length;

  int (*back)        (struct kc_list_t* self, struct kc_node_t** back_node);
  int (*clear)       (struct kc_list_t* self);
  int (*empty)       (struct kc_list_t* self, bool* is_empty);
  int (*erase)       (struct kc_list_t* self, int index);
  int (*front)       (struct kc_list_t* self, struct kc_node_t** front_node);
  int (*get)         (struct kc_list_t* self, int index, struct kc_node_t** node);
  int (*insert)      (struct kc_list_t* self, int index, void* data, size_t size);
  int (*pop_back)    (struct kc_list_t* self);
  int (*pop_front)   (struct kc_list_t* self);
  int (*push_back)   (struct kc_list_t* self, void* data, size_t size);
  int (*push_front)  (struct kc_list_t* self, void* data, size_t size);
  int (*remove)      (struct kc_list_t* self, void* value, int (*compare)(const void* a, const void* b));
  int (*search)      (struct kc_list_t* self, void* value, int (*compare)(const void* a, const void* b), bool* exists);
};

struct kc_list_t* new_list      ();
void              destroy_list  (struct kc_list_t *list);

//---------------------------------------------------------------------------//

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

//---------------------------------------------------------------------------//

#endif /* KC_LIST_T_H */
