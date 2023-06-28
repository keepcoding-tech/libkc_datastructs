#include "../include/dictionary.h"

// MARK: PUBLIC MEMBER METHODS
void insert_dict(struct Dictionary* self, void* key,
    size_t key_size, void* value, size_t value_size);
void* search_dict(struct Dictionary* self, void* key, size_t key_size);

// MARK: PRIVATE MEMBER METHODS
void recursive_dictionary_destroy(struct Node* node);

// The constructor takes a "compare" function pointer as its only argument
// and returns a defined Dictionary struct.
struct Dictionary* new_dictionary(int (*compare)(void* key_one, void* key_two)) {
  // create a Dictionary instance to be returned
  struct Dictionary* dictionary = malloc(sizeof(struct Dictionary));

  // initialize the structure members fields
  dictionary->binary_tree = new_binary_tree(compare);
  dictionary->keys = new_linked_list();

  // assigns the public member methods
  dictionary->insert = insert_dict;
  dictionary->search = search_dict;

  return dictionary;
}

// Destroy the linked list and the binary search tree to free the memory.
void destroy_dictionary(struct Dictionary* dictionary) {
  // free the linked list memory
  destroy_linked_list(dictionary->keys);

  // free the binary tree memory
  if (dictionary->binary_tree->root != NULL) {
    recursive_dictionary_destroy(dictionary->binary_tree->root);
  }

  // free the instance too
  free(dictionary);
}

// This function adds items to the dictionary - the user does not
// need to implement elements themselves.
void insert_dict(struct Dictionary* self, void* key,
    size_t key_size, void* value, size_t value_size) {
  // create a new Entry
  struct Entry* entry = entry_constructor(key, key_size, value, value_size);

  // insert that entry into the tree
  self->binary_tree->insert(self->binary_tree, entry, sizeof(struct Entry));
}

// This function finds the value for a given key in the Dictionary.
void* search_dict(struct Dictionary* self, void* key, size_t key_size) {
  // create a new entry
  int dummy_value = 0;

  struct Entry* searchable = entry_constructor(key, key_size,
      &dummy_value, sizeof(dummy_value));

  // use the iterate function of the BinaryTree to find the desired node
  struct Node* result_node =
      self->binary_tree->search(self->binary_tree, searchable);

  // get the entry from the node
  struct Entry* result_entry = (struct Entry*)result_node->data;

  // return either the value for that key or NULL if not found
  if (result_entry != NULL) {
    return result_entry->value;
  }

  return NULL;
}

// This function will use "Depth First Search" algorithm to destruct the tree.
void recursive_dictionary_destroy(struct Node* node) {
  // chekc the previous node
  if (node->prev != NULL) {
    recursive_dictionary_destroy(node->prev);
  }

  // chekc the next node
  if (node->next != NULL) {
    recursive_dictionary_destroy(node->next);
  }

  // destroy the entry
  entry_destructor(node->data);
}

// Compare two integers casting them into Entry.
int dict_compare_int(void* entry_one, void* entry_two) {
  return (*(int*)(((struct Entry*)entry_one)->key) -
      *(int*)(((struct Entry*)entry_two)->key));
}

// Compare two string casting them into Entry.
int dict_compare_str(void* entry_one, void* entry_two) {
  return strcmp((char*)(((struct Entry*)entry_one)->key),
      (char*)(((struct Entry*)entry_two)->key));
}
