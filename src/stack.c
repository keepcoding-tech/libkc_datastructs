#include "../include/stack.h"

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
void* get_top_item_stack(struct Stack* self);
size_t get_vector_length_stack(struct Stack* self);
void insert_top_item_stack(struct Stack* self, void* data, size_t size);
void remove_top_item_stack(struct Stack* self);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor is used to create new instances of stack.
struct Stack* new_stack() {
  // create a Stack instance to be returned
  struct Stack* new_stack = malloc(sizeof(struct Stack));

  // confirm that there is memory to allocate
  if (new_stack == NULL) {
    printf("keepcoding/Stack ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  // instantiate the stack's Vector via the constructor
  new_stack->vector = new_vector();

  // make sure the vector was initialized correctely
  if (new_stack->vector == NULL) {
    /* an error has already been throw */
    return NULL;
  }

  // assigns the public member methods
  new_stack->length = get_vector_length_stack;
  new_stack->pop = remove_top_item_stack;
  new_stack->push = insert_top_item_stack;
  new_stack->top = get_top_item_stack;

  return new_stack;
}

// The destructor removes all the items by calling the Vector destructor.
void destroy_stack(struct Stack* stack) {
  // destroy stack only if is not dereferenced
  if (stack == NULL) {
    printf("keepcoding/Stack ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Dereferenced object!\n");
    return;
  }

  destroy_vector(stack->vector);
  free(stack);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This function returns the data from the last item in the array.
void* get_top_item_stack(struct Stack* self) {
  return self->vector->back(self->vector);
}

// This function returns the length of the vector.
size_t get_vector_length_stack(struct Stack* self) {
  return self->vector->length;
}

// This function adds an item to the end of the vector.
void insert_top_item_stack(struct Stack* self, void* data, size_t size) {
  // utilize the push_back from Vector with enforced parameters
  self->vector->push_back(self->vector, data, size);
}

// This function removes the last item in the vector.
void remove_top_item_stack(struct Stack* self) {
  // utilize the erase from Vector with enforced parameters
  self->vector->pop_back(self->vector);
}

