#include "Queue.h"

// MARK: PUBLIC MEMBER METHODS

void * peek(struct Queue *queue);
void pop(struct Queue *queue);
void push(struct Queue *queue, void *data, unsigned long size);

// The constructor is used to create new instances of queue.
struct Queue queue_constructor() {
  // create a Queue instance to be returned
  struct Queue queue;

  // instantiate the queue's LinkedList via the constructor
  queue.list = linked_list_constructor();

  // assigns the public member methods
  queue.push = push;
  queue.peek = peek;
  queue.pop = pop;

  return queue;
}

// The destructor removes all the nodes by calling the linked list destructor.
void queue_destructor(struct Queue *queue) {
  linked_list_destructor(&queue->list);
}

// The "peek" function returns the data from the first item in the chain.
void * peek(struct Queue *queue) {
  // utilize the retrieve function from LinkedList with enforced parameters
  struct Node *node_data = queue->list.retrieve(0, &queue->list);

  return node_data->data;
}

// The "pop" function removes the first item in the chain.
void pop(struct Queue *queue) {
  // utilize the remove function from LinkedList with enforced parameters
  queue->list.remove(0, &queue->list);
}

// The "push" function adds an item to the end of the list.
void push(struct Queue *queue, void *data, unsigned long size) {
  // utilize insert from LinkedList with enforced parameters
  queue->list.insert(queue->list.length, data, &queue->list, size);
}
