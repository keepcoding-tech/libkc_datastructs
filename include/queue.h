// open source c library
// ==================================
//
// queue.h
//
// Daniel Tanase
// 22/06/2023

/*
 * The Queue struct is a modified version of the List that enforces
 * specific rules regarding the addition and retrieval of items. In this
 * structure, items are consistently added to the end of the queue and removed
 * from the front. The methods implemented in the Queue struct primarily make
 * use of the corresponding methods in List in a predefined manner.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

#include <stdlib.h>

struct Queue {
  // a reference to the embedded List
  struct List* list;

  // returns the length of the list
  size_t (*length)(struct Queue* self);

  // retrieves the data from the front of the list
  void* (*peek)(struct Queue* self);

  // removes the first item in the list
  void (*pop)(struct Queue* self);

  // adds a node to the end of the chain
  void (*push)(struct Queue* self, void* data, size_t size);
};

// the constructor should be used to create Queues
struct Queue* new_queue();

// the destructor should be used to destroy a Queues
void destroy_queue(struct Queue* queue);

#endif /* QUEUE_H */
