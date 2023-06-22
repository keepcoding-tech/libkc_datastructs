#include "../include/binary_tree.h"

void insert_bst(struct BinaryTree *self, void *data, size_t size);
struct Node* search_bst(struct BinaryTree *self, void *data);

struct Node* create_node_bst(void *data, size_t size);
void destroy_node_bst(struct Node *node_to_destroy);
void recursive_destroy_binary_tree(struct Node *node);

// The constructor takes a "compare" function pointer as its only argument and
// returns a defined BinaryTree struct.
struct BinaryTree new_binary_tree(int (*compare)(void *data_one, void *data_two)) {
  // create a BinaryTree instance to be returned
  struct BinaryTree new_binary_tree;

  // initialize the structure members fields
  new_binary_tree.root = NULL;

  // assigns the public member methods
  new_binary_tree.compare = compare;
  new_binary_tree.insert = insert_bst;
  new_binary_tree.search = search_bst;

  return new_binary_tree;
}

// The destructor takes a BinaryTree structure pointer as its only
// argument and calls the "recursive_destroy_binary_tree" too free
// the memory of all nodes.
void destroy_binary_tree(struct BinaryTree *binary_tree) {
  if (binary_tree->root != NULL) {
    recursive_destroy_binary_tree(binary_tree->root);
  }
}

// To insert a new node into the tree, we need to mantain the order property.
struct Node* insert_node_bst(struct BinaryTree *self,
  struct Node *node, void *data, size_t size) {
  // check if this is the first node in the tree
  if (!node) {
    node = create_node_bst(data, size);

    // check if the current node's data is smaller (move to left)
  } else if (self->compare(data, node->data) < 0) {
    node->prev = insert_node_bst(self, node->prev, data, size);

    // check if the current node's data is greater (move to right)
  } else if (self->compare(data, node->data) > 0) {
    node->next = insert_node_bst(self, node->next, data, size);
  }

  return node;
}

// This function adds new nodes to the tree
void insert_bst(struct BinaryTree *self, void *data, size_t size) {
  self->root = insert_node_bst(self, self->root, data, size);
}

// This function utilizes the iterate function to test if a given
// node exists in the tree. If the node is found, its data is returned.
// Otherwise, NULL is returned.
struct Node* search_bst(struct BinaryTree *self, void *data) {
  // start searching from the root of the tree
  struct Node *current = self->root;

  while (current) {
      // check if the current node's data is greater (move to left)
    if (self->compare(current->data, data) > 0) {
      current = current->prev;

      // check if the current node's data is smaller (move to right)
    } else if (self->compare(current->data, data) < 0) {
      current = current->next;
    } else {
      // the desired node was found, return it
      return current;
    }
  }

  // if the node was not found, return NULL
  return NULL;
}

// This allocates space on the heap for a node and uses the
// Node constructor to instantiate it.
struct Node* create_node_bst(void *data, size_t size) {
  // allocate space
  struct Node* new_node = malloc(sizeof *new_node);

  // call the constructor
  new_node = node_constructor(data, size);

  return new_node;
}

// This function removes a node by deallocating it's memory
// address, this simply renames the node destructor function.
void destroy_node_bst(struct Node *node_to_destroy) {
  node_destructor(node_to_destroy);
}

// This function will use "Depth First Search" algorithm to destruct the tree.
void recursive_destroy_binary_tree(struct Node *node) {
  // chekc the previous node
  if (node->prev != NULL) {
    recursive_destroy_binary_tree(node->prev);
  }

  // check the next node
  if (node->next != NULL) {
    recursive_destroy_binary_tree(node->next);
  }

  // destroy the node
  destroy_node_bst(node);
}

// Compare two integers and return if the first one is bigger, smaller or equal.
int compare_int(void *data_one, void *data_two) {
  return (*(int *)data_one - *(int *)data_two);
}

// Compare two strings and return if the first one is greater, smaller or equal.
int compare_str(void *data_one, void *data_two) {
  return strcmp(data_one, data_two);
}
