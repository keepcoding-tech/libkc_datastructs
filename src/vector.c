// This file is part of libkc_datastructs
// ==================================
//
// vector.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/exceptions.h"
#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static void erase_all_elems(struct Vector* self);
static void erase_elem(struct Vector* self, int index);
static void erase_elems_by_value(struct Vector* self, void* value, int (*compare)(const void* a, const void* b));
static void erase_first_elem(struct Vector* self);
static void erase_last_elem(struct Vector* self);
static void* get_elem(struct Vector* self, int index);
static void* get_first_elem(struct Vector* self);
static void* get_last_elem(struct Vector* self);
static size_t get_vector_capacity(struct Vector* self);
static void insert_at_beginning(struct Vector* self, void* data, size_t size);
static void insert_at_end(struct Vector* self, void* data, size_t size);
static bool is_vector_empty(struct Vector* self);
static void insert_new_elem(struct Vector* self, int index, void* data, size_t size);
static void resize_vector_capacity(struct Vector* self, size_t new_capacity);
static bool search_elem(struct Vector* self, void* value, int (*compare)(const void* a, const void* b));

//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static void permute_to_left(struct Vector* vector, int start, int end);
static void permute_to_right(struct Vector* vector, int start, int end);
static void resize_vector(struct Vector* vector, size_t new_capacity);

//---------------------------------------------------------------------------//

struct Vector* new_vector()
{
  struct ConsoleLog* logger = new_console_log(err, log_err, __FILE__);

  // create a Vector instance to be returned
  struct Vector* new_vector = malloc(sizeof(struct Vector));

  // confirm that there is memory to allocate
  if (new_vector == NULL)
  {
    logger->error(logger, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    destroy_console_log(logger);

    // free the instance and exit
    free(new_vector);
    exit(1);
  }

  // initialize the structure members fields
  new_vector->capacity = 16;
  new_vector->length   = 0;
  new_vector->data     = malloc(16 * sizeof(void*));
  new_vector->log      = logger;

  // confirm that there is memory to allocate
  if (new_vector->data == NULL)
  {
    logger->error(logger, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    destroy_console_log(logger);

    // free the instances and exit
    free(new_vector->data);
    free(new_vector);
    exit(1);
  }

  // assigns the public member methods
  new_vector->at         = get_elem;
  new_vector->back       = get_last_elem;
  new_vector->clear      = erase_all_elems;
  new_vector->empty      = is_vector_empty;
  new_vector->erase      = erase_elem;
  new_vector->front      = get_first_elem;
  new_vector->insert     = insert_new_elem;
  new_vector->max_size   = get_vector_capacity;
  new_vector->pop_back   = erase_last_elem;
  new_vector->pop_front  = erase_first_elem;
  new_vector->push_back  = insert_at_end;
  new_vector->push_front = insert_at_beginning;
  new_vector->remove     = erase_elems_by_value;
  new_vector->resize     = resize_vector_capacity;
  new_vector->search     = search_elem;

  return new_vector;
}

//---------------------------------------------------------------------------//

void destroy_vector(struct Vector* vector)
{
  // if the vector reference is NULL, do nothing
  if (vector == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

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
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

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
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  // make sure the list is not empty
  if (self->length == 0)
  {
    self->log->error(self->log, KC_ERROR_EMPTY_STRUCTURE, __LINE__, __func__);

    return;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length)
  {
    self->log->error(self->log, KC_ERROR_INDEX_OUT_OF_BOUNDS, __LINE__, __func__);

    return;
  }

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
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

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
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  erase_elem(self, 0);
}

//---------------------------------------------------------------------------//

void erase_last_elem(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  erase_elem(self, self->length - 1);
}

//---------------------------------------------------------------------------//

void* get_elem(struct Vector* self, int index)
{
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  // make sure the list is not empty
  if (self->length == 0)
  {
    self->log->error(self->log, KC_ERROR_EMPTY_STRUCTURE, __LINE__, __func__);

    return NULL;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) 
  {
    self->log->error(self->log, KC_ERROR_INDEX_OUT_OF_BOUNDS, __LINE__, __func__);

    return NULL;
  }

  return self->data[index];
}

//---------------------------------------------------------------------------//

void* get_first_elem(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  return get_elem(self, 0);
}

//---------------------------------------------------------------------------//

void* get_last_elem(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  return get_elem(self, self->length - 1);
}

//---------------------------------------------------------------------------//

size_t get_vector_capacity(struct Vector* self)
{
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return 1;
  }

  return self->capacity;
}

//---------------------------------------------------------------------------//

void insert_at_beginning(struct Vector* self, void* data, size_t size) {
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  insert_new_elem(self, 0, data, size);
}

//---------------------------------------------------------------------------//

void insert_at_end(struct Vector* self, void* data, size_t size)
{
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  insert_new_elem(self, self->length, data, size);
}

//---------------------------------------------------------------------------//

bool is_vector_empty(struct Vector* self) {
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  return self->length == 0;
}

//---------------------------------------------------------------------------//

void insert_new_elem(struct Vector* self, int index, void* data, size_t size)
{
  // if the vector reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  // confirm the user has specified a valid index
  if (index < 0 || index > self->length)
  {
    self->log->error(self->log, KC_ERROR_INDEX_OUT_OF_BOUNDS, __LINE__, __func__);

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
    self->log->error(self->log, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);

    return;
  }

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
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

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
  // make sure the user specific a valid capacity size
  if (new_capacity < 1)
  {
    vector->log->error(vector->log, KC_ERROR_UNDERFLOW, __LINE__, __func__);
    return;
  }

  // temporarlly store the new data
  void** new_data = realloc(vector->data, new_capacity * sizeof(void*));

  // check if the memory reallocation was succesfull
  if (new_data == NULL)
  {
    vector->log->error(vector->log, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    return;
  }

  vector->data = new_data;
  vector->capacity = new_capacity;
}

//---------------------------------------------------------------------------//
