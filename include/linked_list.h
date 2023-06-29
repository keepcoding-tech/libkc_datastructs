// open source c library
// ==================================
//
// linked_list.h
//
// Daniel Tanase
// 20/06/2023

/*
 * The LinkedList struct represents a dynamic implementation of a linked list,
 * consisting of interconnected Nodes. Each Node points to the next and
 * previous nodes in the chain. Unlike static implementations, this LinkedList
 * allows for flexible data types and can be resized as needed.
 *
 * The LinkedList object simplifies the process of creating and destroying
 * nodes automatically, enabling users to focus on inserting their desired data.
 * To accommodate various data types, node data is stored as void pointers,
 * requiring appropriate casting when accessed.
 *
 * To create and destroy instances of the LinkedList struct, it is recommended
 * to use the constructor and destructor functions.
 *
 * It's important to note that when using member functions, a reference to the
 * LinkedList instance needs to be passed, similar to how "self" is passed to
 * class member functions in Python. This allows for accessing and manipulating
 * the LinkedList object's data and behavior.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
  // points to the first and last node in the chain
  struct Node* head;
  struct Node* tail;

  // length refers to the number of nodes in the chain
  size_t length;

  // adds new items to the chain at a specified location
  void (*add)(struct LinkedList* self, int index, void* data, size_t size);

  // allows data in the chain to be accessed
  struct Node* (*get)(struct LinkedList* self, int index);

  // return either if the list is empty or not
  bool (*is_empty)(struct LinkedList* self);

  // deletes an item from the chain and handles the deallocation of memory
  void (*remove)(struct LinkedList* self, int index);

  // search a specified node by value
  bool (*search)(struct LinkedList* self, void*  query,
      bool (*compare)(void* data_one, void* data_two));
};

// the constructor should be used to create linked lists
struct LinkedList* new_linked_list();

// the destructor should be used to destroy linked lists
void destroy_linked_list(struct LinkedList *linked_list);

#endif /* LINKEDLIST_H */
