// open source c library
// ==================================
//
// Dictionary.h
//
// Daniel Tanase
// 15/1/22

/*
 Dictionary is defined as a general-purpose data structure for storing a
 group of objects. A Dictionary is associated with a set of keys and each key
 has a single associated value.

 When presented with a key, the dictionary will simply return the associated
 value. The items do not have to be in a certain order because the key-value
 pair can be of any type of data.
*/

#ifndef Dictionary_h
#define Dictionary_h

#include "LinkedList.h"
#include "BinarySearchTree.h"
#include "Entry.h"

// The dictionary is a collection of entries stored in a BinarySearchTree.
struct Dictionary {
  // inheriting the BinarySearchTree object
  struct BinarySearchTree binary_search_tree;
  // a linked list to store the dictionary keys for easy iteration
  struct LinkedList keys;

  // insert adds new items to the dictionary - the user need only specify the
  // key, value, and their respective sizes
  void (*insert)(struct Dictionary *self, void *key,
    unsigned long key_size, void *value, unsigned long value_size);
  // search looks for a given key in the dictionary and returns its
  // value if found or NULL if not
  void * (*search)(struct Dictionary *self, void *key, unsigned long key_size);
};

// MARK: CONSTRUCTORS

// The constructor should be used to create Dictionaries.
struct Dictionary dictionary_constructor(
  int (*compare)(void *key_one, void *key_two));
// The destructor should be used to destroy a Dictionaries.
void dictionary_destructor(struct Dictionary *dictionary);

// MARK: PUBLIC HELPER FUNCTIONS

// Compare two integers casting them into Entry.
int compare_int_keys(void *entry_one, void *entry_two);
// Compare two string casting them into Entry.
int compare_str_keys(void *entry_one, void *entry_two);

#endif /* Dictionary_h */
