// open source c library
// ==================================
//
// Node.h
//
// Daniel Tanase
// 10/1/22

/*
 The Node struct is the foundation for list objects, functioning like a single
 cell in the list. Nodes utilize void pointers to store data, and as such are
 capable of storing any data type.

 In order to work, this requires the data to be allocated on the heap prior to
 being inserted into a node object. Typically, this is handled automatically
 when the node constructor is used; however, custom data types (those not
 included in the enumeration) need to be allocated manually and the data type
 "Special" should be used.

 In order to destroy a node, the node destructor is recommended as it will free
 both the stored data and the node itself automatically.
*/

#ifndef Node_h
#define Node_h

// Nodes are used to store data of any type in a list.
struct Node {
  // the data is stored as a void pointer, casting is required for proper access
  void *data;
  // a pointer to the next node in the chain
  struct Node *next;
  // a pointer to the previous node in the chain
  struct Node *prev;
};

// MARK: CONSTRUCTORS

// The constructor should be used to create nodes.
struct Node node_constructor(void *data, unsigned long size);
// The destructor should be used to destroy nodes.
void node_destructor(struct Node *node);

#endif /* Node_h */
