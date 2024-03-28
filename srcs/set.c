// This file is part of keepcoding_core
// ==================================
//
// set.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../../hdrs/common.h"
#include "../../hdrs/datastructs/set.h"

#include <stdlib.h>
#include <string.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static int insert_new_pair_set  (struct kc_set_t* self, void* key, size_t key_size, void* value, size_t value_size);
static int remove_pair_set      (struct kc_set_t* self, void* key, size_t key_size);
static int search_pair_set      (struct kc_set_t* self, void* key, size_t key_size, void** data);

//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static void _recursive_set_destroy  (struct kc_node_t* node);

//---------------------------------------------------------------------------//

struct kc_set_t* new_set(int (*compare)(const void* a, const void* b))
{
  // create a Set instance to be returned
  struct kc_set_t* new_set = malloc(sizeof(struct kc_set_t));

  // confirm that there is memory to allocate
  if (new_set == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return NULL;
  }

  // create a console log instance to be used for the set
  new_set->_logger = new_logger(KC_SET_LOG_PATH);

  if (new_set->_logger == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    // free the set instance
    free(new_set);

    return NULL;
  }

  // instantiate the set's kc_tree_t via the constructor
  new_set->_entries = new_tree(compare);

  if (new_set->_entries == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    // free the set instances
    destroy_logger(new_set->_logger);
    free(new_set);

    return NULL;
  }

  // assigns the public member methods
  new_set->insert = insert_new_pair_set;
  new_set->remove = remove_pair_set;
  new_set->search = search_pair_set;

  return new_set;
}

//---------------------------------------------------------------------------//

void destroy_set(struct kc_set_t* set)
{
  // if the set reference is NULL, do nothing
  if (set == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    return;
  }

  // free the binary tree memory
  if (set->_entries->root != NULL)
  {
    _recursive_set_destroy(set->_entries->root);
  }

  destroy_logger(set->_logger);

  // free the instance too
  free(set);
}

//---------------------------------------------------------------------------//

int insert_new_pair_set(struct kc_set_t* self, void* key, size_t key_size, void* value, size_t value_size)
{
  // if the set reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // check if the pair already exists in the set
  struct kc_node_t* node = NULL;
  int ret = search_pair_set(self, key, key_size, &node->data);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  if (node != NULL)
  {
    return KC_SUCCESS;
  }

  // create a new Pair
  struct kc_pair_t* pair = pair_constructor(key, key_size, value, value_size);

  // insert that pair into the tree
  ret = self->_entries->insert(self->_entries, pair, sizeof(struct kc_pair_t));

  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int remove_pair_set(struct kc_set_t* self, void* key, size_t key_size)
{
  // if the set reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // create a new pair by using a dummy value
  char dummy_value = 'a';
  struct kc_pair_t* pair_to_remove = pair_constructor(key, key_size,
      &dummy_value, sizeof(char));

  if (pair_to_remove == NULL)
  {
    return KC_INVALID;
  }

  // call the remove function of the Tree structure
  int ret = self->_entries->remove(self->_entries, pair_to_remove, sizeof(struct kc_pair_t));
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  pair_destructor(pair_to_remove);

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int search_pair_set(struct kc_set_t* self, void* key, size_t key_size, void** value)
{
  // if the set reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // create a new pair by using a dummy value
  char dummy_value = 'a';
  struct kc_pair_t* searchable = pair_constructor(key, key_size,
      &dummy_value, sizeof(char));

  if (searchable == NULL)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, KC_OUT_OF_MEMORY,
      __FILE__, __LINE__, __func__);

    return KC_OUT_OF_MEMORY;
  }

  // use the search function of the kc_tree_t to find the desired node
  struct kc_node_t* result_node = NULL;
  int ret = self->_entries->search(self->_entries, searchable, &result_node);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  // free the dummy pair
  pair_destructor(searchable);

  // make sure the node was found
  if (result_node != NULL)
  {
    // get the pair from the node
    struct kc_pair_t* result_pair = (struct kc_pair_t*)result_node->data;

    // return either the value for that key
    if (result_pair != NULL && result_pair->value != NULL)
    {
      (*value) = result_pair->value;
    }
    else
    {
      // return NULL if not found
      value = NULL;
    }
  }
  else
  {
    // return NULL if not found
    value = NULL;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

void _recursive_set_destroy(struct kc_node_t* node)
{
  // chekc the previous node
  if (node->prev != NULL)
  {
    _recursive_set_destroy(node->prev);
  }

  // check the next node
  if (node->next != NULL)
  {
    _recursive_set_destroy(node->next);
  }

  // destroy the pair
  pair_destructor(node->data);
}

//---------------------------------------------------------------------------//
