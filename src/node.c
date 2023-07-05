#include "../include/node.h"

// The constructor is used to create new instances of nodes.
struct Node* node_constructor(void* data, size_t size) {
  // confirm the size of the data is at least one
  if (size < 1) {
    printf("keepcoding/Node ... \n");
    printf("Error code: Invalid data size for node!\n");
    return NULL;
  }

  // create a Node instance to be returned
  struct Node* node = malloc(sizeof(struct Node));

  // confirm that there is memory to allocate
  if (node == NULL) {
    printf("keepcoding/Node ... \n");
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  // allocate space for the data
  node->data = malloc(size);

  // confirm that there is memory to allocate
  if (node->data == NULL) {
    printf("keepcoding/Node ... \n");
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  // copy the block of memory
  memcpy(node->data, data, size);

  // initialize the pointers
  node->next = NULL;
  node->prev = NULL;

  return node;
}

// The destructor removes a node by freeing the node's data and its node.
void node_destructor(struct Node* node) {
  free(node->data);
  free(node);
}
