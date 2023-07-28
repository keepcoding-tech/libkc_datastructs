#include "../include/set.h"

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
void insert_new_entry_set(struct Set* self, void* key,
    size_t key_size, void* value, size_t value_size);
void remove_entry_set(struct Set* self, void* key);
void* search_entry_set(struct Set* self, void* key, size_t key_size);

// MARK: PRIVATE MEMBER METHODS PROTOTYPES
void recursive_set_destroy(struct Node* node);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor takes a "compare" function pointer as its
// only argument and returns a defined Set struct.
struct Set* new_set(int (*compare)(const void* a, const void* b)) {
  // create a Set instance to be returned
  struct Set* new_set = malloc(sizeof(struct Set));

  // confirm that there is memory to allocate
  if (new_set == NULL) {
    printf("keepcoding/Set ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  new_set->entries = new_tree(compare);

  // confirm that the tree was initialize correctely
  if (new_set->entries == NULL) {
    printf("keepcoding/Set ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  // assigns the public member methods
  new_set->insert = insert_new_entry_set;
  new_set->remove = remove_entry_set;
  new_set->search = search_entry_set;

  return new_set;
}

// Destroy the linked list and the binary search tree to free the memory.
void destroy_set(struct Set* set) {
  // destroy set only if is not dereferenced
  if (set == NULL) {
    printf("keepcoding/Set ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Dereferenced object!\n");
    return;
  }

  // free the binary tree memory
  if (set->entries->root != NULL) {
    recursive_set_destroy(set->entries->root);
  }

  // free the instance too
  free(set);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function adds items to the set - the user does not
// need to implement elements themselves.
void insert_new_entry_set(struct Set* self, void* key,
    size_t key_size, void* value, size_t value_size) {
  // check if the entry already exists in the set
  if (search_entry_set(self, key, key_size) != NULL) {
    return;
  }

  // create a new Entry
  struct Entry* entry = entry_constructor(key, key_size, value, value_size);

  // insert that entry into the tree
  self->entries->insert(self->entries, entry, sizeof(struct Entry));
}

// This function removes a specified element based on the key.
void remove_entry_set(struct Set* self, void* key) {

}

// This function finds the value for a given key in the Set.
void* search_entry_set(struct Set* self, void* key, size_t key_size) {
  // create a new entry by using a dummy value
  char dummy_value = 'a';
  struct Entry* searchable = entry_constructor(key, key_size,
      &dummy_value, sizeof(char));

  // use the search function of the Tree to find the desired node
  struct Node* result_node =
      self->entries->search(self->entries, searchable);

  // free the dummy entry
  entry_destructor(searchable);

  // make sure the node was found
  if (result_node != NULL) {
    // get the entry from the node
    struct Entry* result_entry = (struct Entry*)result_node->data;

    // return either the value for that key or NULL if not found
    if (result_entry != NULL) {
      return result_entry->value;
    }
  }

  return NULL;
}

// MARK: PRIVATE MEMBER METHODS DEFINITIONS

// This function will use "Depth First Search" algorithm to destruct the tree.
void recursive_set_destroy(struct Node* node) {
  // chekc the previous node
  if (node->prev != NULL) {
    recursive_set_destroy(node->prev);
  }

  // check the next node
  if (node->next != NULL) {
    recursive_set_destroy(node->next);
  }

  // destroy the entry
  entry_destructor(node->data);
}

<<<<<<< HEAD
// Compare two integers casting them into Entry.
int dict_compare_int(const void* entry_one, const void* entry_two) {
  return (*(int*)(((struct Entry*)entry_one)->key) -
      *(int*)(((struct Entry*)entry_two)->key));
}

// Compare two string casting them into Entry.
int dict_compare_str(const void* entry_one, const void* entry_two) {
  return strcmp((char*)((struct Entry*)entry_one)->key,
      (char*)((struct Entry*)entry_two)->key);
}
=======
>>>>>>> refactor: set naming conv
