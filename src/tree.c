// This file is part of libkc_datastructs
// ==================================
//
// tree.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/exceptions.h"
#include "../include/tree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//--- MARK: PRIVATE FUNCTION PROTOTYPES -------------------------------------//

static void         insert_new_node_btree   (struct Tree* self, void* data, size_t size);
static void         remove_node_btree       (struct Tree* self, void* data, size_t size);
static struct Node* search_node_btree       (struct Tree* self, void* data);
static struct Node* insert_node_btree       (struct Tree* self, struct Node* node, void* data, size_t size);
static void         recursive_destroy_tree  (struct Node* node);
static struct Node* recursive_remove_node   (struct Tree* self, struct Node* root, void* data, size_t size);

//---------------------------------------------------------------------------//

struct Tree* new_tree(int (*compare)(const void* a, const void* b))
{
  struct ConsoleLog* logger = new_console_log(err, log_err, __FILE__);

  // create a Tree instance to be returned
  struct Tree* new_tree = malloc(sizeof(struct Tree));

  // confirm that there is memory to allocate
  if (new_tree == NULL)
  {
    logger->error(logger, KC_ERROR_OUT_OF_MEMORY, __LINE__, __func__);
    destroy_console_log(logger);

    // free the instance and exit
    free(new_tree);
    exit(1);
  }

  // initialize the structure members fields
  new_tree->root = NULL;
  new_tree->log  = logger;

  // assigns the public member methods
  new_tree->compare = compare;
  new_tree->insert  = insert_new_node_btree;
  new_tree->remove  = remove_node_btree;
  new_tree->search  = search_node_btree;

  return new_tree;
}

//---------------------------------------------------------------------------//

void destroy_tree(struct Tree* tree)
{
  // if the tree reference is NULL, do nothing
  if (tree == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  if (tree->root != NULL)
  {
    recursive_destroy_tree(tree->root);
  }

  // free the binary tree too
  free(tree);
}

//---------------------------------------------------------------------------//

void insert_new_node_btree(struct Tree* self, void* data, size_t size)
{
  // if the tree reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  self->root = insert_node_btree(self, self->root, data, size);
}

//---------------------------------------------------------------------------//

void remove_node_btree(struct Tree* self, void* data, size_t size)
{
  // if the tree reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return;
  }

  self->root = recursive_remove_node(self, self->root, data, size);
}

//---------------------------------------------------------------------------//

struct Node* search_node_btree(struct Tree* self, void* data)
{
  // if the tree reference is NULL, do nothing
  if (self == NULL)
  {
    log_warning("NULL_REFERENCE", "You are attempting to use a reference "
        "or pointer that points to null or is uninitialized.",
        __FILE__, __LINE__, __func__);

    return NULL;
  }

  // start searching from the root of the tree
  struct Node* current = self->root;

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
      return current;
    }
  }

  // if the node was not found, return NULL
  return NULL;
}

//---------------------------------------------------------------------------//

struct Node* insert_node_btree(struct Tree* self,
    struct Node* node, void* data, size_t size)
{
  // check if this is the first node in the tree
  if (!node)
  {
    node = node_constructor(data, size);

  } // check if the current node's data is smaller (move to left)
  else if (self->compare(data, node->data) < 0) 
  {
    node->prev = insert_node_btree(self, node->prev, data, size);

  } // check if the current node's data is greater (move to right)
  else if (self->compare(data, node->data) > 0)
  {
    node->next = insert_node_btree(self, node->next, data, size);
  }

  return node;
}

//---------------------------------------------------------------------------//

void recursive_destroy_tree(struct Node* node)
{
  // chekc the previous node
  if (node->prev != NULL)
  {
    recursive_destroy_tree(node->prev);
  }

  // check the next node
  if (node->next != NULL)
  {
    recursive_destroy_tree(node->next);
  }

  // destroy the node
  node_destructor(node);
}

//---------------------------------------------------------------------------//

struct Node* recursive_remove_node(struct Tree* self, struct Node* root, void* data, size_t size)
{
  // base case
  if (root == NULL)
  {
    return root;
  }

  // recursive calls for ancestors of node to be removed
  if (self->compare(data, root->data) < 0)
  {
    root->prev = recursive_remove_node(self, root->prev, data, size);
    return root;
  }

  if (self->compare(data, root->data) > 0)
  {
    root->next = recursive_remove_node(self, root->next, data, size);
    return root;
  }

  // we reach here when root is the node to be deleted

  // case 1: node has no children or only one child
  if (root->prev == NULL)
  {
    struct Node* next_node = root->next;
    node_destructor(root);
    return next_node;
  }

  if (root->next == NULL)
  {
    struct Node* prev_node = root->prev;
    node_destructor(root);
    return prev_node;
  }

  // case 2: node has two children
  struct Node* succ_parent = root;

  // find successor
  struct Node* successor = root->next;
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
