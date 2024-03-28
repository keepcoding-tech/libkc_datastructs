// This file is part of keepcoding_core
// ==================================
//
// queue.h
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * The Queue struct is a modified version of the List that enforces
 * specific rules regarding the addition and retrieval of items. In this
 * structure, items are consistently added to the end of the queue and removed
 * from the front, following the FIFO (first-in first-out) concept. The methods
 * implemented in the Queue struct primarily make use of the corresponding
 * methods in List in a predefined manner.
 *
 * To create and destroy instances of the List struct, it is recommended
 * to use the constructor and destructor functions.
 *
 * It's important to note that when using member functions, a reference to the
 * Queue instance needs to be passed, similar to how "self" is passed to
 * class member functions in Python. This allows for accessing and manipulating
 * the Queue object's data and behavior.
 */

#ifndef KC_QUEUE_T_H
#define KC_QUEUE_T_H

#include "../system/logger.h"

#include "list.h"

#include <stdio.h>

//---------------------------------------------------------------------------//

#define KC_QUEUE_LOG_PATH  "build/log/queue.log"

//---------------------------------------------------------------------------//

struct kc_queue_t
{
  struct kc_list_t*   _list;
  struct kc_logger_t* _logger;

  int (*length)  (struct kc_queue_t* self, size_t* length);
  int (*peek)    (struct kc_queue_t* self, void** peek);
  int (*pop)     (struct kc_queue_t* self);
  int (*push)    (struct kc_queue_t* self, void* data, size_t size);
};

struct kc_queue_t* new_queue      ();
void               destroy_queue  (struct kc_queue_t* queue);

//---------------------------------------------------------------------------//

#endif /* KC_QUEUE_T_H */
