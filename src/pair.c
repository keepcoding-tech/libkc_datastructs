// This file is part of keepcoding
// ==================================
//
// pair.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/kclog/kclog.h"
#include "../include/pair.h"

#include <stdlib.h>
#include <string.h>

// The constructor is used to create new instances of pair.
struct Pair* pair_constructor(void* key, size_t key_size,
    void* value, size_t value_size) {
  // create a new instance of console_log for loggining
  struct ConsoleLog* log = new_console_log();

  // confirm the size of the data is at least one
  if (key_size < 1 || value_size < 1) {
    log->log_error("UNDERFLOW", "The data type's size goes below its "
        "minimum representable value.", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  // create a Pair instance to be returned
  struct Pair* new_pair = malloc(sizeof(struct Pair));

  // confirm that there is memory to allocate
  if (new_pair == NULL) {
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);

    // free the instance and exit
    free(new_pair);
    exit(1);
  }

  // allocate space on the heap for the key and value
  new_pair->key = malloc(key_size);
  new_pair->value = malloc(value_size);

  // confirm that there is memory to allocate
  if (new_pair->key == NULL || new_pair->value == NULL) {
    log->log_error("OUT_OF_MEMORY", "Failing to allocate memory dynamically "
        "(e.g. using malloc) due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);

    // free the instances and exit
    free(new_pair->key);
    free(new_pair->value);
    free(new_pair);
    exit(1);
  }

  // destroy the console log
  destroy_console_log(log);

  // copy the data parameters into the new object
  memcpy(new_pair->key, key, key_size);
  memcpy(new_pair->value, value, value_size);

  return new_pair;
}

// The destructor must free the key and value of a given pair.
void pair_destructor(struct Pair* pair) {
  // destroy pair only if is not dereferenced
  if (pair == NULL) {
    struct ConsoleLog* log = new_console_log();
    log->log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  free(pair->key);
  free(pair->value);
  free(pair);
}
