#include "../include/vector.h"

// MARK: PUBLIC MEMBER METHODS
void push_v(struct Vector *self, const void *data, size_t size);
size_t max_size_v(struct Vector *self);
void erase_v(struct Vector *self, int index);

// MARK: PRIVATE MEMBER METHODS
void resizeVector(struct Vector* self, size_t new_capacity);

// The constructor is used to create new instances of vector.
struct Vector* new_vector() {
  struct Vector* new_vector = malloc(sizeof(struct Vector));

  // confirm that there is memory to allocate
  if (new_vector == NULL) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  // initialize the structure members fields
  new_vector->capacity = 16;
  new_vector->size = 0;
  new_vector->data = malloc(new_vector->capacity * sizeof(void*));
  new_vector->front = 0;
  new_vector->back = 0;

  // assigns the public member methods
  new_vector->push = push_v;
  new_vector->max_size = max_size_v;
  new_vector->erase = erase_v;

  return new_vector;
}

// The destructor removes all the items.
void destroy_vector(struct Vector *vector) {
  if (vector == NULL) {
    return;
  }

  // Free the memory for each element and the array itself
  for (size_t i = 0; i < vector->size; i++) {
    free(vector->data[i]);
  }

  free(vector->data);
  free(vector);
}

// This function pushs a new item in the vector.
void push_v(struct Vector *self, const void* value, size_t size) {
  // reallocate more memory if the capacity is full
  if (self->size >= self->capacity) {
    resizeVector(self, self->capacity * 2);
  }

  // alocate space to memory
  void* new_elem = malloc(size);

  // check if the memory allocation was succesfull
  if (new_elem == NULL) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return;
  }

  // insert the value at the end of the array
  memcpy(new_elem, value, size);
  self->data[self->size++] = new_elem;
}

// This functino returns the maximum capacity of 
// the vector before reallocating more memory.
size_t max_size_v(struct Vector *self) {
  return (int)self->capacity;
}

// This functino will remove a specific item from the vector.
void erase_v(struct Vector *self, int index) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= self->size) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Index out of bound!\n");
    return;
  }

  // free the memory from the desired position
  for (int i = index; i < self->size; ++i) {
    self->data[i] = self->data[i + 1];
  }

  // resize and free the erased memory
  self->size--;
  free(self->data[self->size]);
}

// This functino will double the capacity of the vector.
void resizeVector(struct Vector* self, size_t new_capacity) {
  // temporarlly store the new data
  void** new_data = realloc(self->data, new_capacity * sizeof(void*));

  // check if the memory reallocation was succesfull
  if (new_data == NULL) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return;
  }

  self->data = new_data;
  self->capacity = new_capacity;
}
