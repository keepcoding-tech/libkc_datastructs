#include "../include/queue.h"

// MARK: PUBLIC MEMBER METHODS
void* peek(struct Queue* self);
void pop_q(struct Queue* self);
void push_q(struct Queue* self, void* data, size_t size);

// The constructor is used to create new instances of queue.
struct Queue* new_queue() {
  // create a Queue instance to be returned
  struct Queue* queue = malloc(sizeof(struct Queue));

  // instantiate the queue's List via the constructor
  queue->list = new_list();

  // assigns the public member methods
  queue->push = push_q;
  queue->peek = peek;
  queue->pop = pop_q;

  return queue;
}

// The destructor removes all the nodes by calling the linked list destructor.
void destroy_queue(struct Queue* queue) {
  destroy_list(queue->list);

  // free the queue too
  free(queue);
}

// This function returns the data from the first item in the chain.
void* peek(struct Queue* self) {
  // check if the head of the list exists
  if (self->list->head != NULL) {
    return self->list->head->data;
  }

  return NULL;
}

// This function removes the first item in the chain.
void pop_q(struct Queue *self) {
  // utilize the remove from List with enforced parameters
  self->list->erase(self->list, 0);
}

// This function adds an item to the end of the list.
void push_q(struct Queue *self, void *data, size_t size) {
  // utilize add from List with enforced parameters
  self->list->insert(self->list, self->list->length, data, size);
}
