// open source c library
// ==================================
//
// Queue.h
//
// Daniel Tanase
// 11/1/22

/*
 The Queue struct is a version of the LinkedList the enforces rules on how
 items are added and accessed. In short, items are always added to the end and
 removed from the front. Largely, the methods defined here simply utilize those
 from LinkedList in a predefined way.
*/

#ifndef Queue_h
#define Queue_h

#include "LinkedList.h"

// Queues are used to access a linked list in a controlled manner.
struct Queue {
  // a reference to the embedded LinkedList
  struct LinkedList list;

  // retrieves the data from the front of the list
  void * (*peek)(struct Queue *self);
  // removes the first item in the list
  void (*pop)(struct Queue *self);
  // adds a node to the end of the chain
  void (*push)(struct Queue *self, void *data, unsigned long size);
};

// MARK: CONSTRUCTORS

// The constructor should be used to create Queues.
struct Queue queue_constructor(void);
// The destructor should be used to destroy a Queues.
void queue_destructor(struct Queue *queue);

#endif /* Queue_h */
