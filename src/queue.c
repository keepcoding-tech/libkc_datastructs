#include "../include/queue.h"

void * peek(struct Queue *self);
void pop(struct Queue *self);
void push(struct Queue *self, void *data, size_t size);

// The constructor is used to create new instances of queue.
struct Queue new_queue() {
  // create a Queue instance to be returned
  struct Queue queue;

  // instantiate the queue's LinkedList via the constructor
  queue.list = new_linked_list();

  // assigns the public member methods
  queue.push = push;
  queue.peek = peek;
  queue.pop = pop;

  return queue;
}

// The destructor removes all the nodes by calling the linked list destructor.
void destroy_queue(struct Queue *queue) {
  destroy_linked_list(&queue->list);
}

// This function returns the data from the first item in the chain.
void * peek(struct Queue *self) {
  // utilize the get function from LinkedList with enforced parameters
  struct Node *node_data = self->list.get(&self->list, 0);
  return node_data->data;
}

// This function removes the first item in the chain.
void pop(struct Queue *self) {
  // utilize the remove function from
  // LinkedList with enforced parameters
  self->list.remove(&self->list, 0);
}

// This function adds an item to the end of the list.
void push(struct Queue *self, void *data, size_t size) {
  // utilize add from LinkedList with enforced parameters
  self->list.add(&self->list, self->list.length, data, size);
}
