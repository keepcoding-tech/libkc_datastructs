#include "../include/tree.h"

// MARK: PUBLIC MEMBER METHODS PROTOTYPES
void insert_new_node_btree(struct Tree* self, void* data, size_t size);
struct Node* search_node_btree(struct Tree* self, void* data);

// MARK: PRIVATE MEMBER METHODS PROTOTYPES
struct Node* insert_node_btree(struct Tree* self,
    struct Node* node, void* data, size_t size);
void recursive_destroy_tree(struct Node* node);

// MARK: CONSTRUCTOR & DESTRUCTOR DEFINITIONS

// The constructor takes a "compare" function pointer as its
// only argument and returns a new instance of tree.
struct Tree* new_tree(int (*compare)(const void* a, const void* b)) {
  // create a Tree instance to be returned
  struct Tree* new_tree = malloc(sizeof(struct Tree));

  // confirm that there is memory to allocate
  if (new_tree == NULL) {
    printf("keepcoding/Tree ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: The memory could not be allocated!\n");
    return NULL;
  }

  // initialize the structure members fields
  new_tree->root = NULL;

  // assigns the public member methods
  new_tree->compare = compare;
  new_tree->insert = insert_new_node_btree;
  new_tree->search = search_node_btree;

  return new_tree;
}

// The destructor takes a Tree structure pointer as its only
// argument and calls the "recursive_destroy_tree" too free
// the memory of all nodes.
void destroy_tree(struct Tree* tree) {
  // destroy tree only if is not dereferenced
  if (tree == NULL) {
    printf("keepcoding/Tree ... \n");
    printf("Error at %s:%d in function %s. \n", __FILE__, __LINE__, __func__);
    printf("Error code: Dereferenced object!\n");
    return;
  }

  if (tree->root != NULL) {
    recursive_destroy_tree(tree->root);
  }

  // free the binary tree too
  free(tree);
}

// This function adds new nodes to the tree
void insert_new_node_btree(struct Tree* self, void* data, size_t size) {
  self->root = insert_node_btree(self, self->root, data, size);
}

// This function utilizes the iterate function to test if a given
// node exists in the tree. If the node is found, its data is returned.
// Otherwise, NULL is returned.
struct Node* search_node_btree(struct Tree* self, void* data) {
  // start searching from the root of the tree
  struct Node* current = self->root;

  while (current != NULL) {
    // check if the current node's data is greater (move to left)
    if (self->compare(current->data, data) > 0) {
      current = current->prev;

      // check if the current node's data is smaller (move to right)
    } else if (self->compare(current->data, data) < 0) {
      current = current->next;

      // the desired node was found, return it
    } else {
      return current;
    }
  }

  // if the node was not found, return NULL
  return NULL;
}

// MARK: PRIVATE MEMBER METHODS DEFINITIONS

// To insert a new node into the tree, we need to mantain the order property.
struct Node* insert_node_btree(struct Tree* self,
    struct Node* node, void* data, size_t size) {
  // check if this is the first node in the tree
  if (!node) {
    node = node_constructor(data, size);

    // check if the current node's data is smaller (move to left)
  } else if (self->compare(data, node->data) < 0) {
    node->prev = insert_node_btree(self, node->prev, data, size);

    // check if the current node's data is greater (move to right)
  } else if (self->compare(data, node->data) > 0) {
    node->next = insert_node_btree(self, node->next, data, size);
  }

  return node;
}

// This function will use "Depth First Search" algorithm to destruct the tree.
void recursive_destroy_tree(struct Node* node) {
  // chekc the previous node
  if (node->prev != NULL) {
    recursive_destroy_tree(node->prev);
  }

  // check the next node
  if (node->next != NULL) {
    recursive_destroy_tree(node->next);
  }

  // destroy the node
  node_destructor(node);
}

