// This file is part of keepcoding_core
// ==================================
//
// vector.h
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * A dynamic vector refers to a data structure that allows for the efficient
 * manipulation of a collection of elements. Unlike static arrays, dynamic
 * vectors can change in size during runtime, offering flexibility in handling
 * varying amounts of data.
 *
 * Typically implemented as a dynamically allocated array, a dynamic vector can
 * be resized dynamically.This enables the vector to grow or shrink as needed,
 * accommodating the addition or removal of elements. The dynamic nature of the
 * vector ensures efficient memory utilization and facilitates dynamic data
 * storage, retrieval, and modification.
 *
 * To create and destroy instances of the Vector struct, it is recommended
 * to use the constructor and destructor functions.
 *
 * It's important to note that when using member functions, a reference to the
 * Vector instance needs to be passed, similar to how "self" is passed to
 * class member functions in Python. This allows for accessing and manipulating
 * the Vector object's data and behavior.
 */

#ifndef KC_VECTOR_T_H
#define KC_VECTOR_T_H

#include "../system/logger.h"

#include <stdbool.h>
#include <stdio.h>

//---------------------------------------------------------------------------//

#define KC_VECTOR_LOG_PATH  "build/log/vector.log"

//---------------------------------------------------------------------------//

struct kc_vector_t
{
  size_t              _capacity;
  struct kc_logger_t* _logger;

  void** data;
  size_t length;

  int (*at)          (struct kc_vector_t* self, int index, void** at);
  int (*back)        (struct kc_vector_t* self, void** back);
  int (*clear)       (struct kc_vector_t* self);
  int (*empty)       (struct kc_vector_t* self, bool* empty);
  int (*erase)       (struct kc_vector_t* self, int index);
  int (*front)       (struct kc_vector_t* self, void** front);
  int (*insert)      (struct kc_vector_t* self, int index, void* data, size_t size);
  int (*max_size)    (struct kc_vector_t* self, size_t* max_size);
  int (*pop_back)    (struct kc_vector_t* self);
  int (*pop_front)   (struct kc_vector_t* self);
  int (*push_back)   (struct kc_vector_t* self, void* data, size_t size);
  int (*push_front)  (struct kc_vector_t* self, void* data, size_t size);
  int (*remove)      (struct kc_vector_t* self, void* value, int (*compare)(const void* a, const void* b));
  int (*resize)      (struct kc_vector_t* self, size_t new_capacity);
  int (*search)      (struct kc_vector_t* self, void* value, int (*compare)(const void* a, const void* b), bool* exists);
};

struct kc_vector_t* new_vector      ();
void                destroy_vector  (struct kc_vector_t* vector);

//---------------------------------------------------------------------------//

#define COMPARE_VECTOR(type, function_name)         \
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

#endif /* VECTOR_T_H */
