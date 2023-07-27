// open source c library
// ==================================
//
// set.h
//
// Daniel Tanase
// 22/06/2023

/*
 * A Dictionary is a versatile data structure used for storing a collection of
 * objects. It is characterized by a set of keys, where each key corresponds to
 * a single associated value.
 *
 * When provided with a specific key, the dictionary retrieves the corresponding
 * value. The order of the items in the dictionary is not predetermined, as the
 * key-value pairs can accommodate various types of data.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "list.h"
#include "tree.h"
#include "entry.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Dictionary {
  // inheriting the Tree object
  struct Tree* tree;

  // a linked list to store the dictionary keys for easy iteration
  struct List* keys;

  // adds new items to the dictionary. Only the key, value,
  // and their respective sizes need to be specified.
  void (*insert)(struct Dictionary* self, void* key,
    size_t key_size, void* value, size_t value_size);

  // scans the dictionary for a specified key and returns its corresponding
  // value, if the key is not found, the function returns NULL.
  void* (*search)(struct Dictionary* self, void* key, size_t key_size);
};

// the constructor should be used to create Dictionaries
struct Dictionary* new_dictionary(int (*compare)(void* key_one, void* key_two));

// the destructor should be used to destroy a Dictionaries
void destroy_dictionary(struct Dictionary* dictionary);

// compare two integers casting them into Entry
int dict_compare_int(void* entry_one, void* entry_two);

// compare two string casting them into Entry
int dict_compare_str(void* entry_one, void* entry_two);

#endif /* DICTIONARY_H */
