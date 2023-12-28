// This file is part of libkc_datastructs
// ==================================
//
// pair.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc/logger/logger.h"
#include "../include/pair.h"

#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------//

struct Pair* pair_constructor(void* key, size_t key_size, void* value, size_t value_size) 
{
  // confirm the size of the data is at least one
  if (key_size < 1 || value_size < 1)
  {
    log_error("UNDERFLOW", "The data type's size goes below its "
        "minimum representable value.", __FILE__, __LINE__, __func__);
    return NULL;
  }

  // create a Pair instance to be returned
  struct Pair* new_pair = malloc(sizeof(struct Pair));

  // confirm that there is memory to allocate
  if (new_pair == NULL)
  {
    log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);

    // free the instance and exit
    free(new_pair);
    exit(1);
  }

  // allocate space on the heap for the key and value
  new_pair->key   = malloc(key_size);
  new_pair->value = malloc(value_size);

  // confirm that there is memory to allocate
  if (new_pair->key == NULL || new_pair->value == NULL)
  {
    log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);

    // free the instances and exit
    free(new_pair->key);
    free(new_pair->value);
    free(new_pair);
    exit(1);
  }

  // copy the data parameters into the new object
  memcpy(new_pair->key, key, key_size);
  memcpy(new_pair->value, value, value_size);

  return new_pair;
}

//---------------------------------------------------------------------------//

void pair_destructor(struct Pair* pair) 
{
  // destroy pair only if is not dereferenced
  if (pair == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);
    return;
  }

  free(pair->key);
  free(pair->value);
  free(pair);
}

//---------------------------------------------------------------------------//
