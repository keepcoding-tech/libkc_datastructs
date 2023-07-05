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
#define CUSTOM_NODE(type, node_name) \
  struct node_name {                 \
    type data;                       \
    struct node_name* next;          \
    struct node_name* prev;          \
  };                                 \
                                     \
  struct node_name* node_name##_constructor(type data) {             \
    struct Node* node = node_constructor(&data, sizeof(type));       \
    if (node != NULL) {                                              \
      struct node_name* new_node = malloc(sizeof(struct node_name)); \
      new_node->data = *(type*)node->data;                           \
      new_node->next = NULL;                                         \
      new_node->prev = NULL;                                         \
      node_destructor(node);                                         \
      return new_node;                                               \
    }                                                                \
    return NULL;                                                     \
  }                                                                  \
                                                                     \
  void node_name##_destructor(struct node_name* node) { \
    free(node);                                         \
  }

#define NODE(type) CUSTOM_NODE(type, Node_##type)

#endif /* NODE_H */
