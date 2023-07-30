#include "../include/node.h"
#include "../deps/kclog/kclog.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// The constructor is used to create new instances of nodes.
struct Node* node_constructor(void* data, size_t size) {
  // create a console log for displaing errors
  struct ConsoleLog* log = new_console_log();

  // confirm the size of the data is at least one
  if (size < 1) {
    log->log_warning("UNDERFLOW", "Data size value is below its minimum "
        "representable value!", __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return NULL;
  }

  // create a Node instance to be returned
  // and allocate space for the data
  struct Node* new_node = malloc(sizeof(struct Node));
  new_node->data = malloc(size);

  // confirm that there is memory to allocate
  if (new_node->data == NULL) {
    log->log_warning("OUT_OF_MEMORY", "Failing to allocate memory "
        "dynamically (using 'malloc') due to insufficient memory in the heap.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);
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
  // create a console log for displaing errors
  struct ConsoleLog* log = new_console_log();

  // destroy node only if is not dereferenced
  if (node == NULL) {
    log->log_warning("NULL_REFERENCE", "Attempting to use a reference "
        "or pointer that points to NULL, or is uninitialized.",
        __FILE__, __LINE__, __func__);
    destroy_console_log(log);
    return;
  }

  free(node->data);
  free(node);
}
