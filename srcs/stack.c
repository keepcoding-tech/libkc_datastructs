// This file is part of keepcoding_core
// ==================================
//
// stack.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../../hdrs/datastructs/stack.h"
#include "../../hdrs/common.h"

#include <stdlib.h>

//--- MARK: PUBLIC FUNCTION PROTOTYPES --------------------------------------//

static int get_top_item_stack       (struct kc_stack_t* self, void** top);
static int get_vector_length_stack  (struct kc_stack_t* self, size_t* length);
static int insert_top_item_stack    (struct kc_stack_t* self, void* data, size_t size);
static int remove_top_item_stack    (struct kc_stack_t* self);

//---------------------------------------------------------------------------//

struct kc_stack_t* new_stack()
{
  // create a Stack instance to be returned
  struct kc_stack_t* new_stack = malloc(sizeof(struct kc_stack_t));

  // confirm that there is memory to allocate
  if (new_stack == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return NULL;
  }

  // instantiate the stack's Vector via the constructor
  new_stack->_vector = new_vector();

  if (new_stack->_vector == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    free(new_stack);

    return NULL;
  }

  new_stack->_logger = new_logger(KC_STACK_LOG_PATH);

  if (new_stack->_logger == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    free(new_stack->_vector);
    free(new_stack);

    return NULL;
  }

  // assigns the public member methods
  new_stack->length = get_vector_length_stack;
  new_stack->pop    = remove_top_item_stack;
  new_stack->push   = insert_top_item_stack;
  new_stack->top    = get_top_item_stack;

  return new_stack;
}

//---------------------------------------------------------------------------//

void destroy_stack(struct kc_stack_t* stack)
{
  // if the stack reference is NULL, do nothing
  if (stack == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return;
  }

  destroy_logger(stack->_logger);
  destroy_vector(stack->_vector);
  free(stack);
}

//---------------------------------------------------------------------------//

int get_top_item_stack(struct kc_stack_t* self, void** top)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  int ret = self->_vector->back(self->_vector, top);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int get_vector_length_stack(struct kc_stack_t* self, size_t* length)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);

    return KC_NULL_REFERENCE;
  }

  (*length) = self->_vector->length;

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int insert_top_item_stack(struct kc_stack_t* self, void* data, size_t size)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // utilize the push_back from Vector with enforced parameters
  int ret = self->_vector->push_back(self->_vector, data, size);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//

int remove_top_item_stack(struct kc_stack_t* self)
{
  // if the stack reference is NULL, do nothing
  if (self == NULL)
  {
    log_error(KC_NULL_REFERENCE_LOG);
    return KC_NULL_REFERENCE;
  }

  // utilize the erase from Vector with enforced parameters
  int ret = self->_vector->pop_back(self->_vector);
  if (ret != KC_SUCCESS)
  {
    self->_logger->log(self->_logger, KC_WARNING_LOG, ret,
      __FILE__, __LINE__, __func__);

    return ret;
  }

  return KC_SUCCESS;
}

//---------------------------------------------------------------------------//
