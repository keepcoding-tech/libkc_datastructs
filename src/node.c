#include "../include/node.h"

// The constructor is used to create new instances of nodes.
struct Node* node_constructor(void* data, size_t size) {
  // confirm the size of the data is at least one
  if (size < 1) {
    printf("keepcoding/Node ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Invalid data size for node!\n");
    return NULL;
  }

  // create a Node instance to be returned
  // and allocate space for the data
  struct Node* new_node = malloc(sizeof(struct Node));
  new_node->data = malloc(size);

  // confirm that there is memory to allocate
  if (new_node->data == NULL) {
    printf("keepcoding/Node ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  // copy the block of memory
  memcpy(new_node->data, data, size);

  // initialize the pointers
  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

// The destructor removes a node by freeing the node's data and its node.
void node_destructor(struct Node* node) {
  // destroy node only if is not dereferenced
  if (node == NULL) {
    printf("keepcoding/Node ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Dereferenced object!\n");
    return;
  }

  free(node->data);
  free(node);
}
