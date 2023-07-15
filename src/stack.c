#include "../include/stack.h"

// MARK: PUBLIC MEMBER METHODS
void pop_s(struct Stack* self);
void push_s(struct Stack* self, void* data, size_t size);

// The constructor is used to create new instances of stack.
struct Stack* new_stack() {
  // create a Stack instance to be returned
  struct Stack* stack = malloc(sizeof(struct Stack));

  // instantiate the stack's Vector via the constructor
  stack->vector = new_vector();

  // assigns the public member methods
  stack->pop = pop_s;
  stack->push = push_s;

  return stack;
}

// The destructor removes all the items by calling the Vector destructor.
void destroy_stack(struct Stack* stack) {
  destroy_vector(stack->vector);

  // free the stack too
  free(stack);
}

// This function removes the last item in the vector.
void pop_s(struct Stack* self) {
  // utilize the erase from Vector with enforced parameters
  self->vector->erase(self->vector, 0);
}

// This function adds an item to the end of the vector.
void push_s(struct Stack* self, void* data, size_t size) {
  // utilize the push from Vector with enforced parameters
  self->vector->insert(self->vector, self->vector->length, data, size);
}
