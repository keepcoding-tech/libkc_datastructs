#include "../include/entry.h"

// The constructor is used to create new instances of entry.
struct Entry* entry_constructor(void* key, size_t key_size,
    void* value, size_t value_size) {

  // confirm the size of the data is at least one
  if (key_size < 1 || value_size < 1) {
    printf("keepcoding/Entry ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Invalid data size for entry!\n");
    exit(1);
  }

  // create a Entry instance to be returned
  struct Entry* entry = malloc(sizeof(struct Entry));

  // allocate space on the heap for the key and value
  entry->key = malloc(key_size);
  entry->value = malloc(value_size);

  // confirm that there is memory to allocate
  if (entry->key == NULL || entry->value == NULL) {
    printf("keepcoding/Entry ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    exit(1);
  }

  // copy the data parameters into the new object
  memcpy(entry->key, key, key_size);
  memcpy(entry->value, value, value_size);

  return entry;
}

// The destructor must free the key and value of a given entry.
void entry_destructor(struct Entry* entry) {
  free(entry->key);
  free(entry->value);
  free(entry);
}
