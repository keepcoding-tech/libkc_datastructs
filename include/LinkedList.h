// open source c library
// ==================================
//
// LinkedList.h
//
// Daniel Tanase
// 10/1/22

/*
 The LinkedList struct is a collection of Nodes, each pointing to the next and
 the previous one in the chain. This is a dynamic implementation of a linked
 list - it does not enforce ubiquitous data types and can be resized at any
 point.

 The object handles the creation and destruction of nodes automatically,
 allowing the user to simply insert the desired data. In order to provide this
 functionality, node data takes the form of void pointers, so it must be casted
 appropriately upon access.

 The constructor and destructor should be used to create and destroy instances
 of the LinkedList struct.

 Note that a reference to the LinkedList instance must be passed to the member
 functions. This is similar to passing "self" to class member functions in
 Python.
*/

#ifndef LinkedList_h
#define LinkedList_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"

// Linked lists are used to move between and manipulate related nodes.
struct LinkedList {
  // head points to the first node in the chain
  struct Node *head;
  // length refers to the number of nodes in the chain
  int length;

  // adds new items to the chain at a specified location
  void (*add)(struct LinkedList *self,
    int index, void *data, unsigned long size);
  // allows data in the chain to be accessed
  struct Node * (*get)(struct LinkedList *self, int index);
  // return either if the list is empty or not
  bool (*is_empty)(struct LinkedList *self);
  // deletes an item from the chain and handles the deallocation of memory
  void (*remove)(struct LinkedList *self, int index);
  // search a specified node by value
  bool (*search)(struct LinkedList *self, void *query,
    bool (*compare)(void *data_one, void *data_two));
};

// MARK: CONSTRUCTORS

// The constructor should be used to create linked lists.
struct LinkedList linked_list_constructor(void);
// The destructor should be used to destroy linked lists.
void linked_list_destructor(struct LinkedList *linked_list);

#endif /* LinkedList_h */
