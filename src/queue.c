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
  struct Queue* new_queue = malloc(sizeof(struct Queue));

  // instantiate the queue's List via the constructor
  new_queue->list = new_list();

  // assigns the public member methods
  new_queue->length = get_list_length_queue;
  new_queue->peek = get_next_item_queue;
  new_queue->pop = remove_next_item_queue;
  new_queue->push = insert_next_item_queue;

  return new_queue;
}

// The destructor removes all the nodes by calling the linked list destructor.
void destroy_queue(struct Queue* queue) {
  // destroy queue only if is not dereferenced
  if (queue == NULL) {
    printf("keepcoding/Queue ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Dereferenced object!\n");
    return;
  }

  destroy_list(queue->list);
  free(queue);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function returns the length of the list.
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

