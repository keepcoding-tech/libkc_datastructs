// open source c library
// ==================================
//
// entry.h
//
// Daniel Tanase
// 22/06/2023

/*
 * Entries serve as the fundamental units of sets, comprising a value that is
 * stored and a key used for identification. This key-value structure enables
 * the storage of data of any type within the set.
 */

#ifndef ENTRY_H
#define ENTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Entry {
  void* key;
  void* value;
};

// the constructor should be used to create Entries
struct Entry* entry_constructor(void* key, size_t key_size,
    void* value, size_t value_size);

// the destructor should be used to destroy a Entries
void entry_destructor(struct Entry* entry);

#endif /* ENTRY_H */
