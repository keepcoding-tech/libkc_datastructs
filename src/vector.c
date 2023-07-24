#include "../include/vector.h"

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
// void erase_all_elems(struct Vector* self);
void erase_elem(struct Vector* self, int index);
// void erase_first_elem(struct Vector* self);
// void erase_last_elem(struct Vector* self);
// void erase_elems_by_value(struct Vector* self, void* value,
    // int (*compare)(const void* a, const void* b));
void* get_elem(struct Vector* self, int index);
// void* get_first_elem(struct Vector* self);
// void* get_last_elem(struct Vector* self);
size_t get_vector_capacity(struct Vector* self);
// void insert_at_beginning(struct Vector* self);
// void insert_at_end(struct Vector* self);
// bool is_vector_empty(struct Vector* self);
void insert_new_elem(struct Vector* self, int index, void* data, size_t size);
// void resize_vector_capacity(struct Vector* self, size_t new_capacity);
// bool search_elem(struct Vector* self, void* value,
    // int (*compare)(const void* a, const void* b));

// MARK: PRIVATE MEMBER METHODS PROTOTYPES
void permute_to_left(struct Vector* vector, int start, int end);
void permute_to_right(struct Vector* vector, int start, int end);
void resize_vector(struct Vector* vector, size_t new_capacity);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor is used to create new instances of vector.
struct Vector* new_vector() {
  // create a Vector instance to be returned
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
  new_vector->length = 0;
  new_vector->data = malloc(16 * sizeof(void*));

  // confirm that there is memory to allocate
  if (new_vector->data == NULL) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");

    // the memory for the vector was allocated, so we need to free it
    free(new_vector);
    return NULL;
  }

  // assigns the public member methods
  new_vector->at = get_elem;
  // new_vector->back = get_last_elem;
  // new_vector->clear = erase_all_elems;
  // new_vector->empty = is_vector_empty;
  new_vector->erase = erase_elem;
  // new_vector->front = get_first_elem;
  new_vector->insert = insert_new_elem;
  new_vector->max_size = get_vector_capacity;
  // new_vector->pop_back = erase_last_elem;
  // new_vector->pop_front = erase_first_elem;
  // new_vector->push_back = insert_at_end;
  // new_vector->push_front = insert_at_beginning;
  // new_vector->remove = erase_elems_by_value;
  // new_vector->resize = resize_vector_capacity;
  // new_vector->search = search_elem;

  return new_vector;
}

// The destructor removes all the items.
void destroy_vector(struct Vector* vector) {
  if (vector == NULL) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Dereferenced object!\n");
    return;
  }

  // Free the memory for each element and the array itself
  for (int i = 0; i < vector->length; ++i) {
    free(vector->data[i]);
  }

  free(vector->data);
  free(vector);
}

// MARK: PUBLIC MEMBER METHODS DEFINITIONS

// This functino will remove a specific item from the vector.
void erase_elem(struct Vector* self, int index) {
  // confirm the user has specified a valid index
  if (index < 0 || index >= self->length) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Index out of bound!\n");
    return;
  }

  // free the memory from the desired position
  permute_to_left(self, index, self->length);
  free(self->data[self->length]);
  --self->length;
}

void* get_elem(struct Vector* self, int index) {
  // confirm the user has specified a valid index
  if (index < 0 || index > self->length) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Index out of bound!\n");
    return NULL;
  }

  return self->data[index];
}

// This functino returns the maximum capacity of
// the vector before reallocating more memory.
size_t get_vector_capacity(struct Vector* self) {
  return self->capacity;
}

// This function inserts a new item in the vector.
void insert_new_elem(struct Vector* self, int index, void* data, size_t size) {
  // confirm the user has specified a valid index
  if (index < 0 || index > self->length) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Index out of bound!\n");
    return;
  }

  // reallocate more memory if the capacity is full
  if (self->length + 1 >= self->capacity) {
    resize_vector(self, self->capacity * 2);
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

  // insert the value at the specified location
  memcpy(new_elem, data, size);
  permute_to_right(self, index, self->length);
  self->data[index] = new_elem;
  ++self->length;
}

// MARK: PRIVATE MEMBER METHODS DEFINITIONS

// This function will permute all the elements (to the left) from the
// starting point specified to the ending point specified.
void permute_to_left(struct Vector* vector, int start, int end) {
  for (int i = start; i < end; ++i) {
    vector->data[i] = vector->data[i + 1];
  }
}

// This function will permute all the elements (to the right) from the
// starting point specified to the ending point specified.
void permute_to_right(struct Vector* vector, int start, int end) {
  for (int i = end; i >= start; --i) {
    vector->data[i] = vector->data[i - 1];
  }
}

// This functino will double the capacity of the vector.
void resize_vector(struct Vector* vector, size_t new_capacity) {
  // temporarlly store the new data
  void** new_data = realloc(vector->data, new_capacity * sizeof(void*));

  // check if the memory reallocation was succesfull
  if (new_data == NULL) {
    printf("keepcoding/Vector ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return;
  }

  vector->data = new_data;
  vector->capacity = new_capacity;
}

