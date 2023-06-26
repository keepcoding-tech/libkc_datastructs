#include "../include/stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the creation and destruction of a stack.
void test_creation_and_destruction() {
  struct Stack* stack = new_stack();
  assert(stack->vector->data[0] == NULL);
  destroy_stack(stack);
}

// Test case for the push() method.
void test_push() {
  struct Stack* stack = new_stack();

  // push 10 new items
  for (int i = 0; i < 10; ++i) {
    stack->push(stack, &i, sizeof(i));

    // check the length of the list
    assert(stack->vector->size == i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    // check if the nodes have been pushed correctly
    assert(*(int*)stack->vector->data[i] == i);
  }
  
  destroy_stack(stack);
}

// Test case for the pop() method.
void test_pop() {
  struct Stack* stack = new_stack();

  // push ten new nodes (if the test reached here then the "push"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    stack->push(stack, &i, sizeof(i));
  }

  for (int i = 1; i < 10; ++i) {
    stack->pop(stack);

    // check if the items have been removed correctly
    assert(stack->vector->size == 10 - i);
  }
  
  destroy_stack(stack);
}

int main() {
  test_creation_and_destruction();
  test_push();
  test_pop();
  printf("stack.t .................... OK\n");
  return 0;
}
