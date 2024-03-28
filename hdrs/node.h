// This file is part of keepcoding_core
// ==================================
//
// node.h
//
// Copyright (c) 2024 Daniel Tanase
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

#ifndef KC_NODE_T_H
#define KC_NODE_T_H

#include "../system/logger.h"

#include <stdio.h>

//---------------------------------------------------------------------------//

#define KC_NODE_LOG_PATH  "build/log/node.log"

//---------------------------------------------------------------------------//

struct kc_node_t
{
  struct kc_node_t* next;
  struct kc_node_t* prev;

  void* data;
};

struct kc_node_t* node_constructor  (void* data, size_t size);
void              node_destructor   (struct kc_node_t* node);

//---------------------------------------------------------------------------//

#endif /* KC_NODE_T_H */
