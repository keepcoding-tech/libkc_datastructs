// This file is part of libkc_datastructs
// ==================================
//
// vector.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/kclog/kclog.h"
#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>

//--- MARK: PUBLIC MEMBER METHODS PROTOTYPES --------------------------------//
void erase_all_elems(struct Vector* self);
void erase_elem(struct Vector* self, int index);
void erase_elems_by_value(struct Vector* self, void* value,
    int (*compare)(const void* a, const void* b));
void erase_first_elem(struct Vector* self);
void erase_last_elem(struct Vector* self);
void* get_elem(struct Vector* self, int index);
void* get_first_elem(struct Vector* self);
void* get_last_elem(struct Vector* self);
size_t get_vector_capacity(struct Vector* self);
void insert_at_beginning(struct Vector* self, void* data, size_t size);
void insert_at_end(struct Vector* self, void* data, size_t size);
bool is_vector_empty(struct Vector* self);
void insert_new_elem(struct Vector* self, int index, void* data, size_t size);
void resize_vector_capacity(struct Vector* self, size_t new_capacity);
bool search_elem(struct Vector* self, void* value,
    int (*compare)(const void* a, const void* b));

//--- MARK: PRIVATE MEMBER METHODS PROTOTYPES -------------------------------//
bool check_vector_reference(struct Vector* vector);
void permute_to_left(struct Vector* vector, int start, int end);
void permute_to_right(struct Vector* vector, int start, int end);
void resize_vector(struct Vector* vector, size_t new_capacity);

//---------------------------------------------------------------------------//

struct Vector* new_vector()
{
  // create a new instance of console_log for loggining
  struct ConsoleLog* log = new_console_log();

  // create a Vector instance to be returned
  struct Vector* new_vector = malloc(sizeof(struct Vector));

  // confirm that there is memory to allocate
  if (new_vector == NULL)
  {
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);

    // free the instance and exit
    free(new_vector);
    exit(1);
  }

  // initialize the structure members fields
  new_vector->capacity = 16;
  new_vector->length = 0;
  new_vector->data = malloc(16 * sizeof(void*));

  // confirm that there is memory to allocate
  if (new_vector->data == NULL)
  {
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);

    // free the instances and exit
    free(new_vector->data);
    free(new_vector);
    exit(1);
  }

  // free the console_log
  destroy_console_log(log);

  // assigns the public member methods
  new_vector->at = get_elem;
  new_vector->back = get_last_elem;
  new_vector->clear = erase_all_elems;
  new_vector->empty = is_vector_empty;
  new_vector->erase = erase_elem;
  new_vector->front = get_first_elem;
  new_vector->insert = insert_new_elem;
  new_vector->max_size = get_vector_capacity;
  new_vector->pop_back = erase_last_elem;
  new_vector->pop_front = erase_first_elem;
  new_vector->push_back = insert_at_end;
  new_vector->push_front = insert_at_beginning;
  new_vector->remove = erase_elems_by_value;
  new_vector->resize = resize_vector_capacity;
  new_vector->search = search_elem;

  return new_vector;
}

//---------------------------------------------------------------------------//

void destroy_vector(struct Vector* vector) {
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(vector) == false)
  {
    return;
  }

  // free the memory for each element and the array itself
  for (int i = 0; i < vector->length; ++i)
  {
    if (vector->data[i] != NULL)
    {
      free(vector->data[i]);
    }
  }

  free(vector->data);
  free(vector);
}

//---------------------------------------------------------------------------//

void erase_all_elems(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  // free the memory for each element
  for (int i = 0; i < self->length; ++i)
  {
    if (self->data[i] != NULL)
    {
      free(self->data[i]);
    }
  }

  // reallocate the default capacity
  if (self->capacity > 16)
  {
    resize_vector(self, 16);
  }

  // reset the length
  self->length = 0;
}

//---------------------------------------------------------------------------//

void erase_elem(struct Vector* self, int index)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  // create a new instance of console_log for loggining
  struct ConsoleLog* log = new_console_log();

  // make sure the list is not empty
  if (self->length == 0)
  {
    log->log_error("EMPTY_STRUCTURE", "You are attempting to perform "
        "operations on an empty data structure" ,__FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    log->log_warning("INDEX_OUT_OF_BOUNDS", "You are trying to access an "
        "element at an invalid index in an array, list, or other indexed "
        "data structure.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // destroy the console log
  destroy_console_log(log);

  // free the memory from the desired position
  permute_to_left(self, index, self->length);
  --self->length;

  // resize if the length of the vector is less than half
  if (self->length < self->capacity / 2 && self->capacity > 16)
  {
    resize_vector(self, self->capacity / 2);
  }
}

//---------------------------------------------------------------------------//

void erase_elems_by_value(struct Vector* self, void* value,
    int (*compare)(const void* a, const void* b))
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  // go through the array and check each element
  int index = 0;
  while (index < self->length)
  {
    if (compare(self->data[index], value) == 0)
    {
      erase_elem(self, index);
      continue;
    }
    ++index;
  }
}

//---------------------------------------------------------------------------//

void erase_first_elem(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  erase_elem(self, 0);
}

//---------------------------------------------------------------------------//

void erase_last_elem(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  erase_elem(self, self->length - 1);
}

//---------------------------------------------------------------------------//

void* get_elem(struct Vector* self, int index)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return NULL;
  }

  // create a new instance of console_log for loggining
  struct ConsoleLog* log = new_console_log();

  // make sure the list is not empty
  if (self->length == 0)
  {
    log->log_error("EMPTY_STRUCTURE", "You are attempting to perform "
        "operations on an empty data structure" ,__FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) 
  {
    log->log_warning("INDEX_OUT_OF_BOUNDS", "You are trying to access an "
        "element at an invalid index in an array, list, or other indexed "
        "data structure.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  // destroy the console log
  destroy_console_log(log);

  return self->data[index];
}

//---------------------------------------------------------------------------//

void* get_first_elem(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return NULL;
  }

  return get_elem(self, 0);
}

//---------------------------------------------------------------------------//

void* get_last_elem(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return NULL;
  }

  return get_elem(self, self->length - 1);
}

//---------------------------------------------------------------------------//

size_t get_vector_capacity(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return 1;
  }

  return self->capacity;
}

//---------------------------------------------------------------------------//

void insert_at_beginning(struct Vector* self, void* data, size_t size) {
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  insert_new_elem(self, 0, data, size);
}

//---------------------------------------------------------------------------//

void insert_at_end(struct Vector* self, void* data, size_t size)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  insert_new_elem(self, self->length, data, size);
}

//---------------------------------------------------------------------------//

bool is_vector_empty(struct Vector* self) {
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return false;
  }

  return self->length == 0;
}

//---------------------------------------------------------------------------//

void insert_new_elem(struct Vector* self, int index, void* data, size_t size)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  // create a new instance of console_log for loggining
  struct ConsoleLog* log = new_console_log();

  // confirm the user has specified a valid index
  if (index < 0 || index > self->length)
  {
    log->log_warning("INDEX_OUT_OF_BOUNDS", "You are trying to access an "
        "element at an invalid index in an array, list, or other indexed "
        "data structure.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // reallocate more memory if the capacity is full
  if (self->length + 1 >= self->capacity)
  {
    resize_vector(self, self->capacity * 2);
  }

  // alocate space in memory
  void* new_elem = malloc(size);

  // check if the memory allocation was succesfull
  if (new_elem == NULL)
  {
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // destroy the console log
  destroy_console_log(log);

  // insert the value at the specified location
  memcpy(new_elem, data, size);
  permute_to_right(self, index, self->length);
  self->data[index] = new_elem;
  ++self->length;
}

//---------------------------------------------------------------------------//

void resize_vector_capacity(struct Vector* self, size_t new_capacity)
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return;
  }

  resize_vector(self, new_capacity);
}

//---------------------------------------------------------------------------//

bool search_elem(struct Vector* self, void* value,
    int (*compare)(const void* a, const void* b))
{
  // if the vector reference is NULL, do nothing
  if (check_vector_reference(self) == false)
  {
    return false;
  }

  // go through the array and return true if found
  for (int i = 0; i < self->length; ++i)
  {
    if (compare(self->data[i], value) == 0)
    {
      return true;
    }
  }

  return false;
}

//---------------------------------------------------------------------------//

bool check_vector_reference(struct Vector* vector)
{
  if (vector == NULL)
  {
    // create a new instance of console_log for loggining
    struct ConsoleLog* log = new_console_log();

    // log the warning to the console
    log->log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    // destroy the console log
    destroy_console_log(log);

    return false;
  }

  return true;
}

//---------------------------------------------------------------------------//

void permute_to_left(struct Vector* vector, int start, int end)
{
  for (int i = start; i < end && i < vector->length; ++i)
  {
    vector->data[i] = vector->data[i + 1];
  }
}

//---------------------------------------------------------------------------//

void permute_to_right(struct Vector* vector, int start, int end)
{
  for (int i = end; i >= start && i > 0; --i)
  {
    vector->data[i] = vector->data[i - 1];
  }
}

//---------------------------------------------------------------------------//

void resize_vector(struct Vector* vector, size_t new_capacity)
{
  // create a new instance of console_log for loggining
  struct ConsoleLog* log = new_console_log();

  // make sure the user specific a valid capacity size
  if (new_capacity < 1)
  {
    log->log_warning("UNDERFLOW", "The data type's size goes below its "
        "minimum representable value.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // temporarlly store the new data
  void** new_data = realloc(vector->data, new_capacity * sizeof(void*));

  // check if the memory reallocation was succesfull
  if (new_data == NULL)
  {
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  // destroy the console log
  destroy_console_log(log);

  vector->data = new_data;
  vector->capacity = new_capacity;
}

//---------------------------------------------------------------------------//
