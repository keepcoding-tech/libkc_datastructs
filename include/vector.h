// open source c library
// ==================================
//
// vector.h
//
// Daniel Tanase
// 23/06/2023

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
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
  // array of data stored as void pointers
  void** data;

  // maximum capacity of the vector
  size_t capacity;

  // current size of the vector
  size_t size;

  // first and last elements of the vector
  int front, back;

  // add new items to the vector
  void (*push)(struct Vector *self, const void *value, size_t size);

  // return the maximum capacity of the vector
  size_t (*max_size)(struct Vector *self);

  // remove a specific item from the vector
  void (*erase)(struct Vector *self, int index);
};

// the constructor should be used to create vectors
struct Vector* new_vector();

// the destructor should be used to destroy vectors
void destroy_vector(struct Vector *vector);

#endif /* VECTOR_H */
