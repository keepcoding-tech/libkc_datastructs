// This file is part of keepcoding
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

#include <stdbool.h>
#include <stdio.h>

struct Vector {
  // array of data stored as void pointers
  void** data;

  // maximum capacity of the vector
  size_t capacity;

  // current size of the vector
  size_t length;

  // returns a reference to the element at position specified
  void* (*at)(struct Vector* self, int index);

  // returns a reference to the last element in the vector
  void* (*back)(struct Vector* self);

  // removes all elements from the vector leaving it with a size of 0
  void (*clear)(struct Vector* self);

  // returns whether the vector is empty or not
  bool (*empty)(struct Vector* self);

  // remove a specific item from the vector
  void (*erase)(struct Vector* self, int index);

  // returns a reference to the first element in the vector
  void* (*front)(struct Vector* self);

  // adds new items to the vector at a specified position
  void (*insert)(struct Vector* self, int index, void* data, size_t size);

  // return the maximum capacity of the vector
  size_t (*max_size)(struct Vector* self);

  // removes the last element in the vector, reducing the size by one
  void (*pop_back)(struct Vector* self);

  // removes the first element in the vector, reducing the size by one
  void (*pop_front)(struct Vector* self);

  // adds a new element at the end of the vector, incrementing the size
  void (*push_back)(struct Vector* self, void* data, size_t size);

  // adds a new element at the beginning of the vector, incrementing the size
  void (*push_front)(struct Vector* self, void* data, size_t size);

  // removes from the vector all the elements that compare equal to value
  void (*remove)(struct Vector* self, void* value,
      int (*compare)(const void* a, const void* b));

  // resizes the vector so that it contains "n" elements
  void (*resize)(struct Vector* self, size_t new_capacity);

  // search a specified element by value
  bool (*search)(struct Vector* self, void* value,
      int (*compare)(const void* a, const void* b));
};

// the constructor should be used to create vectors
struct Vector* new_vector();

// the destructor should be used to destroy vectors
void destroy_vector(struct Vector* vector);

// use this macro to define any type of primitive data comparison function
#define COMPARE_VECTOR(type, function_name) \
  int function_name(const void* a, const void* b) { \
    if (*(type*)a < *(type*)b) {                    \
      return -1;                                    \
    }                                               \
    if (*(type*)a > *(type*)b) {                    \
      return 1;                                     \
    }                                               \
    return 0;                                       \
  }

#endif /* VECTOR_H */
