// open source c library
// ==================================
//
// node.h
//
// Daniel Tanase
// 20/06/2023

/*
 * The Node struct serves as a fundamental component of list objects, acting as
 * an individual cell within the list. Nodes utilize void pointers to store data,
 * enabling them to accommodate any data type.
 *
 * For the Node to function correctly, the data it stores must be allocated on
 * the heap before being inserted into the Node object. This allocation process
 * is typically handled automatically when using the node constructor. However,
 * for custom data types that are not part of the predefined list, manual
 * allocation is necessary using the "Special" data type.
 *
 * To properly deallocate a Node, it is recommended to use the node destructor.
 * This destructor will automatically free both the stored data and the Node
 * itself.
 */

#ifndef NODE_H
#define NODE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  // the data is stored as a void pointer,
  // casting is required for proper access
  void* data;

  // a pointer to the next node in the chain
  struct Node* next;

  // a pointer to the previous node in the chain
  struct Node* prev;
};

// the constructor should be used to create nodes
struct Node* node_constructor(void* data, size_t size);

// the destructor should be used to destroy nodes
void node_destructor(struct Node* node);

// This macro is designed for primitive data types to
// simplify usage and provide efficient data access.
#define NODE(type) \
  struct Node_##type {        \
    type data;                \
    struct Node_##type* next; \
    struct Node_##type* prev; \
  };                          \
                              \
  struct Node_##type* node_##type(type data) {                    \
    struct Node_##type* node =                                    \
        (struct Node_##type*)malloc(sizeof(struct Node_##type));  \
    if (node == NULL) {                                           \
      printf("keepcoding/Node ... \n");                           \
      printf("Error code: The memory could not be allocated!\n"); \
      return NULL;                                                \
    }                                                             \
    if (!data) {                                                  \
      printf("keepcoding/Node ... \n");                           \
      printf("Error code: Invalid data size for node!\n");        \
      return NULL;                                                \
    }                                                             \
    node->data = data;                                            \
    node->next = NULL;                                            \
    node->prev = NULL;                                            \
    return node;                                                  \
  }                                                               \
                                                                  \
  void node_destructor_##type(struct Node_##type* node) { \
    free(node);                                           \
  }

#endif /* NODE_H */
