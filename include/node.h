// This file is part of libkc_datastructs
// ==================================
//
// node.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

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

struct Node
{
  struct Node* next;
  struct Node* prev;

  void* data;
};

struct Node* node_constructor  (void* data, size_t size);
void         node_destructor   (struct Node* node);

#endif /* NODE_H */
