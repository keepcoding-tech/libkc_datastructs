#include "../include/entry.h"

// The constructor is used to create new instances of entry.
struct Entry* entry_constructor(void* key, size_t key_size,
    void* value, size_t value_size) {
  // confirm the size of the data is at least one
  if (key_size < 1 || value_size < 1) {
    printf("keepcoding/Entry ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Invalid data size for entry!\n");
    return NULL;
  }

  // create a Entry instance to be returned
  struct Entry* new_entry = malloc(sizeof(struct Entry));

  // confirm that there is memory to allocate
  if (new_entry == NULL) {
    printf("keepcoding/Entry ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");

    // free the instance
    free(new_entry);

    return NULL;
  }

  // allocate space on the heap for the key and value
  new_entry->key = malloc(key_size);
  new_entry->value = malloc(value_size);

  // confirm that there is memory to allocate
  if (new_entry->key == NULL || new_entry->value == NULL) {
    printf("keepcoding/Entry ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");

    // free the instance
    free(new_entry->key);
    free(new_entry->value);
    free(new_entry);

    return NULL;
  }

  // copy the data parameters into the new object
  memcpy(new_entry->key, key, key_size);
  memcpy(new_entry->value, value, value_size);

  return new_entry;
}

// The destructor must free the key and value of a given entry.
void entry_destructor(struct Entry* entry) {
  // destroy entry only if is not dereferenced
  if (entry == NULL) {
    printf("keepcoding/Stack ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Dereferenced object!\n");
    return;
  }

  free(entry->key);
  free(entry->value);
  free(entry);
}
