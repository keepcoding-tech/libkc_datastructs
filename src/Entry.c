#include "../include/Entry.h"

#include <stdlib.h>
#include <string.h>

// The constructor is used to create new instances of entry.
struct Entry entry_constructor(void *key, unsigned long key_size,
  void *value, unsigned long value_size) {
  // create a Entry instance to be returned
  struct Entry entry;

  // allocate space on the heap for the key and value
  entry.key = malloc(key_size);
  entry.value = malloc(value_size);

  // copy the data parameters into the new object
  memcpy(entry.key, key, key_size);
  memcpy(entry.value, value, value_size);

  return entry;
}

// The destructor must free the key and value of a given entry.
void entry_destructor(struct Entry *entry) {
  free(entry->key);
  free(entry->value);
}
