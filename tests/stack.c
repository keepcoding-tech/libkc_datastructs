#include "../include/stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the creation and destruction of a stack.
void test_creation_and_destruction() {
  struct Stack* stack = new_stack();
  assert(stack->length(stack) == 0);
  assert(stack->vector->capacity == 16);
  destroy_stack(stack);
}

// Test case for the length() method.
void test_length() {
  struct Stack* stack = new_stack();

  // the length should be zero
  assert(stack->length(stack) == 0);

  // push 10 more items
  for (int i = 0; i < 10; ++i) {
    stack->push(stack, &i, sizeof(int));
  }

  assert(stack->length(stack) == 10);

  stack->vector->clear(stack->vector);

  // should be empty again
  assert(stack->length(stack) == 0);

  destroy_stack(stack);
}

// Test case for the pop() method.
void test_pop() {
  struct Stack* stack = new_stack();

  // push 10 new nodes
  for (int i = 0; i < 10; ++i) {
    stack->push(stack, &i, sizeof(i));
  }

  for (int i = 1; i < 10; ++i) {
    stack->pop(stack);

    // check if the items have been removed correctly
    assert(stack->vector->length == 10 - i);
  }

  destroy_stack(stack);
}

// Test case for the push() method.
void test_push() {
  struct Stack* stack = new_stack();

  // push 10 new items
  for (int i = 0; i < 10; ++i) {
    stack->push(stack, &i, sizeof(i));

    // check the length of the list
    assert(stack->vector->length == i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    // check if the nodes have been pushed correctly
    assert(*(int*)stack->vector->data[i] == i);
  }

  destroy_stack(stack);
}

// Test case for the top() method.
void test_top() {
  struct Stack* stack = new_stack();

  // push 60 more items
  for (int i = 0; i < 60; ++i) {
    stack->push(stack, &i, sizeof(int));

    // check each new item
    assert(*(int*)stack->top(stack) == i);
  }

  // check the capacity of the vector
  assert(stack->vector->capacity == 64);

  destroy_stack(stack);
}

int main() {
  test_creation_and_destruction();
  test_length();
  test_pop();
  test_push();
  test_top();
  printf("stack.t .................... OK\n");
  return 0;
}
