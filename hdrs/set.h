// This file is part of keepcoding_core
// ==================================
//
// set.h
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * A Set is a versatile data structure used for storing a collection of
 * objects. It is characterized by a set of keys, where each key corresponds to
 * a single associated value.
 *
 * When provided with a specific key, the set retrieves the corresponding
 * value. The order of the items in the set is not predetermined, as the
 * key-value pairs can accommodate various types of data.
 *
 * It is important to note that sets are containers that store unique elements.
 *
 * To create and destroy instances of the Set struct, it is recommended
 * to use the constructor and destructor functions.
 *
 * It's important to note that when using member functions, a reference to the
 * Set instance needs to be passed, similar to how "self" is passed to
 * class member functions in Python. This allows for accessing and manipulating
 * the Set object's data and behavior.
 */

#ifndef KC_SET_T_H
#define KC_SET_T_H

#include "../system/logger.h"

#include "tree.h"
#include "pair.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//---------------------------------------------------------------------------//

#define KC_SET_LOG_PATH  "build/log/set.log"

//---------------------------------------------------------------------------//

struct kc_set_t
{
  struct kc_tree_t*   _entries;
  struct kc_logger_t* _logger;

  int (*insert)  (struct kc_set_t* self, void* key, size_t key_size, void* value, size_t value_size);
  int (*remove)  (struct kc_set_t* self, void* key, size_t key_size);
  int (*search)  (struct kc_set_t* self, void* key, size_t key_size, void** value);
};

struct kc_set_t* new_set      (int (*compare)(const void* a, const void* b));
void             destroy_set  (struct kc_set_t* set);

//---------------------------------------------------------------------------//

#define COMPARE_SET(type, function_name)                                               \
  int function_name(const void* a, const void* b)                                      \
  {                                                                                    \
    if (*(type*)((struct kc_pair_t*)a)->key < *(type*)((struct kc_pair_t*)b)->key)     \
    {                                                                                  \
      return -1;                                                                       \
    }                                                                                  \
    if (*(type*)((struct kc_pair_t*)a)->key > *(type*)((struct kc_pair_t*)b)->key)     \
    {                                                                                  \
      return 1;                                                                        \
    }                                                                                  \
    return 0;                                                                          \
  }

//---------------------------------------------------------------------------//

#endif /* KC_SET_T_H */
