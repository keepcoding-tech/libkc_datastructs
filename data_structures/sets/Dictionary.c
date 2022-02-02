/*
 Note: due to the fact that several data structures (in this project) will have
 functions for "insertion", "retrieving", "removing", etc; the name of the
 functions in the implementation of the library will have the notation of "dict"
 at the end, representing -> "dictionary".
*/

#include "Dictionary.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// MARK: PUBLIC MEMBER FUNCTIONS

void insert_dict(struct Dictionary *self, void *key,
  unsigned long key_size, void *value, unsigned long value_size);
void * search_dict(struct Dictionary *self, void *key, unsigned long key_size);

// MARK: PRIVATE MEMBER FUNCTIONS

void recursive_dictionary_destroy(struct Node *node);

// The constructor takes a "compare" function pointer as its only argument
// and returns a defined Dictionary struct.
struct Dictionary dictionary_constructor(
  int (*compare)(void *key_one, void *key_two)) {
  // create a Dictionary instance to be returned
  struct Dictionary dictionary;

  // initialize the structure members fields
  dictionary.binary_search_tree = binary_search_tree_constructor(compare);
  dictionary.keys = linked_list_constructor();

  // assigns the public member methods
  dictionary.insert = insert_dict;
  dictionary.search = search_dict;

  return dictionary;
}

// Destroy the linked list and the binary search tree to free the memory.
void dictionary_destructor(struct Dictionary *dictionary) {
  linked_list_destructor(&dictionary->keys);
  recursive_dictionary_destroy(dictionary->binary_search_tree.head);
}

// The "insert_dict" function adds items to the dictionary - the user does not
// need to implement elements themselves.
void insert_dict(struct Dictionary *self, void *key,
  unsigned long key_size, void *value, unsigned long value_size) {
  // create a new Entry
  struct Entry entry = entry_constructor(key, key_size, value, value_size);

  // insert that entry into the tree
  self->binary_search_tree.insert(
    &self->binary_search_tree, &entry, sizeof(entry));
}

// The "search_dict" function finds the value for a given key in the Dictionary.
void * search_dict(struct Dictionary *self, void *key, unsigned long key_size) {
  // create a new entry
  int dummy_value = 0;
  struct Entry searchable = entry_constructor(key, key_size,
    &dummy_value, sizeof(dummy_value));

  // use the iterate function of the BinarySearchTree to find the desired node
  struct Node *result_node = self->binary_search_tree
    .search(&self->binary_search_tree, &searchable);
  // get the entry from the node
  struct Entry *result_entry = result_node->data;

  // return either the value for that key or NULL if not found
  if (result_entry) {
    return result_entry->value;
  }
  return NULL;
}

// The "recursive_dictionary_destroy" function will use "Depth First Search"
// algorithm to destruct the tree.
void recursive_dictionary_destroy(struct Node *node) {
  // chekc the previous node
  if (node->prev) {
    recursive_dictionary_destroy(node->prev);
  }
  // chekc the next node
  if (node->next) {
    recursive_dictionary_destroy(node->next);
  }

  // destroy the entry
  entry_destructor(node->data);

  // free the data of the nodes
  free(node->data);
  free(node);
}

// Compare two string casting them into Entry.
int compare_string_keys(void *entry_one, void *entry_two) {
  int comparison = strcmp((char *)(((struct Entry *)entry_one)->key),
    (char *)(((struct Entry *)entry_two)->key));

  // the first entry is bigger
  if (comparison > 0) {
    return 1;
  }
  // the first entry is smaller
  if (comparison < 0) {
    return -1;
  }
  // the entries are equal
  return 0;
}
