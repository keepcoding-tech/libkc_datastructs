// This file is part of libkc_datastructs
// ==================================
//
// vector.h
//
// Copyright (c) 2023 Daniel Tanase
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

#ifndef VECTOR_H
#define VECTOR_H

#include "../deps/libkc/logger/logger.h"

#include <stdbool.h>
#include <stdio.h>

struct Vector 
{
  void** data;
  size_t capacity;
  size_t length;

  struct ConsoleLog* log;

  void*  (*at)          (struct Vector* self, int index);
  void*  (*back)        (struct Vector* self);
  void   (*clear)       (struct Vector* self);
  bool   (*empty)       (struct Vector* self);
  void   (*erase)       (struct Vector* self, int index);
  void*  (*front)       (struct Vector* self);
  void   (*insert)      (struct Vector* self, int index, void* data, size_t size);
  size_t (*max_size)    (struct Vector* self);
  void   (*pop_back)    (struct Vector* self);
  void   (*pop_front)   (struct Vector* self);
  void   (*push_back)   (struct Vector* self, void* data, size_t size);
  void   (*push_front)  (struct Vector* self, void* data, size_t size);
  void   (*remove)      (struct Vector* self, void* value, int (*compare)(const void* a, const void* b));
  void   (*resize)      (struct Vector* self, size_t new_capacity);
  bool   (*search)      (struct Vector* self, void* value, int (*compare)(const void* a, const void* b));
};

//---------------------------------------------------------------------------//

struct Vector* new_vector      ();
void           destroy_vector  (struct Vector* vector);

//---------------------------------------------------------------------------//

// use this macro to define any type of primitive data comparison function
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

#endif /* VECTOR_H */
