#include "../include/Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The constructor is used to create new instances of nodes.
struct Node node_constructor(void *data, unsigned long size) {
  // confirm the size of the data is at least one
  if (size < 1) {
    // TODO: return error instead of printing it
    printf("Invalid data size for node...\n");
    exit(1);
  }

  // create a Node instance to be returned
  struct Node node;

  // allocate space for the data if it is of a supported type
  node.data = malloc(size);
  // confirm that there is memory to allocate
  if (node.data == NULL) {
    // TODO: return error instead of printing it
    printf("The memory could not be allocated...\n");
    exit(1);
  }
  memcpy(node.data, data, size);

  // initialize the pointers
  node.next = NULL;
  node.prev = NULL;

  return node;
}

// The destructor removes a node by freeing the node's data and its node.
void node_destructor(struct Node *node) {
  free(node->data);
  free(node);
}
