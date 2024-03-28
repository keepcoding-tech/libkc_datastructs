// This file is part of keepcoding_core
// ==================================
//
// pair.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../../hdrs/datastructs/pair.h"
#include "../../hdrs/common.h"

#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------//

struct kc_pair_t* pair_constructor(void* key, size_t key_size, void* value, size_t value_size)
{
  // confirm the size of the data is at least one
  if (key_size < 1 || value_size < 1)
  {
    log_error(KC_UNDERFLOW_LOG);
    return NULL;
  }

  // create a Pair instance to be returned
  struct kc_pair_t* new_pair = malloc(sizeof(struct kc_pair_t));

  // confirm that there is memory to allocate
  if (new_pair == NULL)
  {
    log_error(KC_OUT_OF_MEMORY_LOG);
    return NULL;
  }

  // allocate space on the heap for the key and value
  new_pair->key   = malloc(key_size);
  new_pair->value = malloc(value_size);

  // confirm that there is memory to allocate
  if (new_pair->key == NULL || new_pair->value == NULL)
  {
    log_error(KC_OUT_OF_MEMORY_LOG);

    // free the instances
    free(new_pair);

    return NULL;
  }

  // copy the data parameters into the new object
  memcpy(new_pair->key, key, key_size);
  memcpy(new_pair->value, value, value_size);

  return new_pair;
}

//---------------------------------------------------------------------------//

void pair_destructor(struct kc_pair_t* pair)
{
  // destroy pair only if is not dereferenced
  if (pair == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return;
  }

  free(pair->key);
  free(pair->value);
  free(pair);
}

//---------------------------------------------------------------------------//
