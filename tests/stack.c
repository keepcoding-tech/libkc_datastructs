// This file is part of libkc_datastructs
// ==================================
//
// stack.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc_testing/testing.h"
#include "../include/stack.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  testgroup("Stack")
  {
    subtest("test creation and destruction")
    {
      struct Stack* stack = new_stack();
      ok(stack->length(stack) == 0);
      ok(stack->vector->capacity == 16);
      destroy_stack(stack);
    }

    subtest("test length")
    {
      struct Stack* stack = new_stack();

      // the length should be zero
      ok(stack->length(stack) == 0);

      // push 10 more items
      for (int i = 0; i < 10; ++i)
      {
        stack->push(stack, &i, sizeof(int));
      }

      ok(stack->length(stack) == 10);

      stack->vector->clear(stack->vector);

      // should be empty again
      ok(stack->length(stack) == 0);

      destroy_stack(stack);
    }

    subtest("test pop")
    {
      struct Stack* stack = new_stack();

      // push 10 new nodes
      for (int i = 0; i < 10; ++i)
      {
        stack->push(stack, &i, sizeof(i));
      }

      for (int i = 1; i < 10; ++i)
      {
        stack->pop(stack);

        // check if the items have been removed correctly
        ok(stack->vector->length == 10 - i);
      }

      destroy_stack(stack);
    }

    subtest("test push")
    {
      struct Stack* stack = new_stack();

      // push 10 new items
      for (int i = 0; i < 10; ++i)
      {
        stack->push(stack, &i, sizeof(i));

        // check the length of the list
        ok(stack->vector->length == i + 1);
      }

      for (int i = 0; i < 10; ++i)
      {
        // check if the nodes have been pushed correctly
        ok(*(int*)stack->vector->data[i] == i);
      }

      destroy_stack(stack);
    }

    subtest("test top")
    {
      struct Stack* stack = new_stack();

      // push 60 more items
      for (int i = 0; i < 60; ++i)
      {
        stack->push(stack, &i, sizeof(int));

        // check each new item
        ok(*(int*)stack->top(stack) == i);
      }

      // check the capacity of the vector
      ok(stack->vector->capacity == 64);

      destroy_stack(stack);
    }

    done_testing()
  }

  return 0;
}
