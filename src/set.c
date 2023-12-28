// This file is part of libkc_datastructs
// ==================================
//
// set.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/exceptions.h"
#include "../include/set.h"

#include <stdlib.h>
#include <string.h>

//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static void  insert_new_pair_set    (struct Set* self, void* key, size_t key_size, void* value, size_t value_size);
static void  remove_pair_set        (struct Set* self, void* key, size_t key_size);
static void* search_pair_set        (struct Set* self, void* key, size_t key_size);
static void  recursive_set_destroy  (struct Node* node);

//---------------------------------------------------------------------------//

struct Set* new_set(int (*compare)(const void* a, const void* b))
{
  struct ConsoleLog* logger = new_console_log(err, log_err, __FILE__);

  // create a Set instance to be returned
  struct Set* new_set = malloc(sizeof(struct Set));

  // confirm that there is memory to allocate
  if (new_set == NULL)
  {
    logger->error(logger, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    destroy_console_log(logger);

    // free the instance and exit
    free(new_set);
    exit(1);
  }

  // instantiate the set's Tree via the constructor
  new_set->entries = new_tree(compare);
  new_set->log     = logger;

  // assigns the public member methods
  new_set->insert = insert_new_pair_set;
  new_set->remove = remove_pair_set;
  new_set->search = search_pair_set;

  return new_set;
}

//---------------------------------------------------------------------------//

void destroy_set(struct Set* set)
{
  // if the set reference is NULL, do nothing
  if (set == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  // free the binary tree memory
  if (set->entries->root != NULL)
  {
    recursive_set_destroy(set->entries->root);
  }

  // free the instance too
  free(set);
}

//---------------------------------------------------------------------------//

void insert_new_pair_set(struct Set* self, void* key,
    size_t key_size, void* value, size_t value_size)
{
  // if the set reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  // check if the pair already exists in the set
  if (search_pair_set(self, key, key_size) != NULL)
  {
    return;
  }

  // create a new Pair
  struct Pair* pair = pair_constructor(key, key_size, value, value_size);

  // insert that pair into the tree
  self->entries->insert(self->entries, pair, sizeof(struct Pair));
}

//---------------------------------------------------------------------------//

void remove_pair_set(struct Set* self, void* key, size_t key_size)
{
  // if the set reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  // create a new pair by using a dummy value
  char dummy_value = 'a';
  struct Pair* pair_to_remove = pair_constructor(key, key_size,
      &dummy_value, sizeof(char));

  // call the remove function of the Tree structure
  self->entries->remove(self->entries, pair_to_remove, sizeof(struct Pair));
  pair_destructor(pair_to_remove);
}

//---------------------------------------------------------------------------//

void* search_pair_set(struct Set* self, void* key, size_t key_size)
{
  // if the set reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  // create a new pair by using a dummy value
  char dummy_value = 'a';
  struct Pair* searchable = pair_constructor(key, key_size,
      &dummy_value, sizeof(char));

  // use the search function of the Tree to find the desired node
  struct Node* result_node =
      self->entries->search(self->entries, searchable);

  // free the dummy pair
  pair_destructor(searchable);

  // make sure the node was found
  if (result_node != NULL)
  {
    // get the pair from the node
    struct Pair* result_pair = (struct Pair*)result_node->data;

    // return either the value for that key or NULL if not found
    if (result_pair != NULL)
    {
      return result_pair->value;
    }
  }

  return NULL;
}

//---------------------------------------------------------------------------//

void recursive_set_destroy(struct Node* node)
{
  // chekc the previous node
  if (node->prev != NULL)
  {
    recursive_set_destroy(node->prev);
  }

  // check the next node
  if (node->next != NULL)
  {
    recursive_set_destroy(node->next);
  }

  // destroy the pair
  pair_destructor(node->data);
}

//---------------------------------------------------------------------------//
