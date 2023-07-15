#include "../include/queue.h"

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
size_t get_list_length_queue(struct Queue* self);
void* get_next_item_queue(struct Queue* self);
void insert_next_item_queue(struct Queue* self, void* data, size_t size);
void remove_next_item_queue(struct Queue* self);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor is used to create new instances of queue.
struct Queue* new_queue() {
  // create a Queue instance to be returned
  struct Queue* queue = malloc(sizeof(struct Queue));

  // instantiate the queue's List via the constructor
  queue->list = new_list();

  // assigns the public member methods
  queue->length = get_list_length_queue;
  queue->peek = get_next_item_queue;
  queue->pop = remove_next_item_queue;
  queue->push = insert_next_item_queue;

  return queue;
}

// The destructor removes all the nodes by calling the linked list destructor.
void destroy_queue(struct Queue* queue) {
  // erase nodes only if the queue is not empty
  if (queue == NULL) {
    //throw_error("Error code: Dereferenced object!", __LINE__, __func__);
    return;
  }

  destroy_list(queue->list);
  free(queue);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function returns the length of the list
size_t get_list_length_queue(struct Queue* self) {
  return self->list->length;
}

// This function returns the data from the first item in the chain.
void* get_next_item_queue(struct Queue* self) {
  struct Node* next_item = self->list->front(self->list);

  // check if the head of the list exists
  if (next_item  != NULL) {
    return next_item->data;
  }

  // return null if non-existing
  return NULL;
}

// This function adds an item to the end of the list.
void insert_next_item_queue(struct Queue *self, void *data, size_t size) {
  self->list->push_back(self->list, data, size);
}

// This function removes the first item in the chain.
void remove_next_item_queue(struct Queue *self) {
  self->list->pop_front(self->list);
}

