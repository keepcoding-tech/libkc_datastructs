// This file is part of libkc_datastructs
// ==================================
//
// set.h
//
// Copyright (c) 2023 Daniel Tanase
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

#ifndef SET_H
#define SET_H

#include "list.h"
#include "tree.h"
#include "pair.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Set 
{
  // inheriting the Tree object for storing data
  struct Tree* entries;

  // adds new items to the set. Only the key, value,
  // and their respective sizes need to be specified
  void (*insert)(struct Set* self, void* key,
      size_t key_size, void* value, size_t value_size);

  // removes a specified element based on the key
  void (*remove)(struct Set* self, void* key, size_t key_size);

  // scans the set for a specified key and returns its corresponding
  // value, if the key is not found, the function returns NULL
  void* (*search)(struct Set* self, void* key, size_t key_size);
};

// the constructor should be used to create Dictionaries
struct Set* new_set(int (*compare)(const void* a, const void* b));

// the destructor should be used to destroy a Dictionaries
void destroy_set(struct Set* set);

// use this macro to define any type of primitive data comparison function
#define COMPARE_SET(type, function_name)                                     \
  int function_name(const void* a, const void* b)                            \
  {                                                                          \
    if (*(type*)((struct Pair*)a)->key < *(type*)((struct Pair*)b)->key)     \
    {                                                                        \
      return -1;                                                             \
    }                                                                        \
    if (*(type*)((struct Pair*)a)->key > *(type*)((struct Pair*)b)->key)     \
    {                                                                        \
      return 1;                                                              \
    }                                                                        \
    return 0;                                                                \
  }

#endif /* set_H */
