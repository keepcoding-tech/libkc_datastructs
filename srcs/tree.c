// This file is part of keepcoding_core
// ==================================
//
// tree.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../../hdrs/common.h"
#include "../../hdrs/datastructs/tree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static int insert_new_node_btree  (struct kc_tree_t* self, void* data, size_t size);
static int remove_node_btree      (struct kc_tree_t* self, void* data, size_t size);
static int search_node_btree      (struct kc_tree_t* self, void* data, struct kc_node_t** node);

//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static struct kc_node_t* _insert_node_btree       (struct kc_tree_t* self, struct kc_node_t* node, void* data, size_t size);
static void              _recursive_destroy_tree  (struct kc_node_t* node);
static struct kc_node_t* _recursive_remove_node   (struct kc_tree_t* self, struct kc_node_t* root, void* data, size_t size);

//---------------------------------------------------------------------------//

struct kc_tree_t* new_tree(int (*compare)(const void* a, const void* b))
{
  // create a Tree instance to be returned
  struct kc_tree_t* new_tree = malloc(sizeof(struct kc_tree_t));

  // confirm that there is memory to allocate
  if (new_tree == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return NULL;
  }

  new_tree->_logger = new_logger(KC_TREE_LOG_PATH);

  // confirm that there is memory to allocate
  if (new_tree->_logger == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    // free the instance
    free(new_tree);

    return NULL;
  }

  // initialize the structure members fields
  new_tree->root = NULL;

  // assigns the public member methods
  new_tree->compare = compare;
  new_tree->insert  = insert_new_node_btree;
  new_tree->remove  = remove_node_btree;
  new_tree->search  = search_node_btree;

  return new_tree;
}

//---------------------------------------------------------------------------//

void destroy_tree(struct kc_tree_t* tree)
{
  // if the tree reference is NULL, do nothing
  if (tree == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return;
  }

  if (tree->root != NULL)
  {
    _recursive_destroy_tree(tree->root);
  }

  destroy_logger(tree->_logger);

  // free the binary tree too
  free(tree);
}

//---------------------------------------------------------------------------//

int insert_new_node_btree(struct kc_tree_t* self, void* data, size_t size)
{
  // if the tree reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  self->root = _insert_node_btree(self, self->root, data, size);

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int remove_node_btree(struct kc_tree_t* self, void* data, size_t size)
{
  // if the tree reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  self->root = _recursive_remove_node(self, self->root, data, size);

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int search_node_btree(struct kc_tree_t* self, void* data, struct kc_node_t** node)
{
  // if the tree reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // start searching from the root of the tree
  struct kc_node_t* current = self->root;

  while (current != NULL)
  {
    // check if the current node's data is greater (move to left)
    if (self->compare(data, current->data) < 0)
    {
      current = current->prev;

      // check if the current node's data is smaller (move to right)
    }
    else if (self->compare(data, current->data) > 0)
    {
      current = current->next;

      // the desired node was found, return it
    }
    else
    {
      (*node) = current;

      return KC_SUCCESS;
    }
  }

  // if the node was not found, return NULL
  (*node) = NULL;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

struct kc_node_t* _insert_node_btree(struct kc_tree_t* self,
    struct kc_node_t* node, void* data, size_t size)
{
  // check if this is the first node in the tree
  if (!node)
  {
    node = node_constructor(data, size);

  } // check if the current node's data is smaller (move to left)
  else if (self->compare(data, node->data) < 0)
  {
    node->prev = _insert_node_btree(self, node->prev, data, size);

  } // check if the current node's data is greater (move to right)
  else if (self->compare(data, node->data) > 0)
  {
    node->next = _insert_node_btree(self, node->next, data, size);
  }

  return node;
}

//---------------------------------------------------------------------------//

void _recursive_destroy_tree(struct kc_node_t* node)
{
  // chekc the previous node
  if (node->prev != NULL)
  {
    _recursive_destroy_tree(node->prev);
  }

  // check the next node
  if (node->next != NULL)
  {
    _recursive_destroy_tree(node->next);
  }

  // destroy the node
  node_destructor(node);
}

//---------------------------------------------------------------------------//

struct kc_node_t* _recursive_remove_node(struct kc_tree_t* self, struct kc_node_t* root, void* data, size_t size)
{
  // base case
  if (root == NULL)
  {
    return root;
  }

  // recursive calls for ancestors of node to be removed
  if (self->compare(data, root->data) < 0)
  {
    root->prev = _recursive_remove_node(self, root->prev, data, size);
    return root;
  }

  if (self->compare(data, root->data) > 0)
  {
    root->next = _recursive_remove_node(self, root->next, data, size);
    return root;
  }

  // we reach here when root is the node to be deleted

  // case 1: node has no children or only one child
  if (root->prev == NULL)
  {
    struct kc_node_t* next_node = root->next;
    node_destructor(root);
    return next_node;
  }

  if (root->next == NULL)
  {
    struct kc_node_t* prev_node = root->prev;
    node_destructor(root);
    return prev_node;
  }

  // case 2: node has two children
  struct kc_node_t* succ_parent = root;

  // find successor
  struct kc_node_t* successor = root->next;
  while (successor->prev != NULL)
  {
    succ_parent = successor;
    successor = successor->prev;
  }

  // since successor is always the left child of its parent we can safely make
  // successor's "next", the next child as "prev" of its parent. If there is no
  // successor, then assign successor' "next" to succ_parent' "next"
  if (succ_parent != root)
  {
    succ_parent->prev = successor->prev;
  }
  else
  {
    succ_parent->next = successor->next;
  }

  // copy successor data to root
  memcpy(root->data, successor->data, size);

  // delete successor and return root
  node_destructor(successor);

  return root;
}

//---------------------------------------------------------------------------//
