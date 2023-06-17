#include "../include/Queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the "push" function.
void push_test() {
  // create a new instance of a Queue
  struct Queue queue = queue_constructor();

  // push ten new nodes
  for (int i = 0; i < 10; ++i) {
    queue.push(&queue, &i, sizeof(i));
    // check the length of the list
    assert(queue.list.length == i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    struct Node *cursor = queue.list.head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been pushed correctly
    assert(*(int *)cursor->data == i);
  }

  queue_destructor(&queue);
}

// Test the "pop" function.
void pop_test() {
  // create a new instance of a Queue
  struct Queue queue = queue_constructor();

  // push ten new nodes (if the test reached here then the "push"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    queue.push(&queue, &i, sizeof(i));
  }

  for (int i = 1; i < 10; ++i) {
    queue.pop(&queue);
    // check if the nodes have been removed correctly
    assert(queue.list.length == 10 - i);
  }

  queue_destructor(&queue);
}

// Test the "peek" function.
void peek_test() {
  // create a new instance of a Queue
  struct Queue queue = queue_constructor();

  // push ten new nodes (if the test reached here then the "push"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    queue.push(&queue, &i, sizeof(i));
  }

  for (int i = 0; i < 10; ++i) {
    // check if the nodes have been peeked correctly
    assert(*(int *)queue.peek(&queue) == i);

    // destroy the first node (if the test reached here then the "pop"
    // function was successfully tested, so we can freely use it)
    queue.pop(&queue);
  }

  queue_destructor(&queue);
}

int main() {
  peek_test();
  pop_test();
  push_test();
  printf("queue.t .................... OK\n");
  return 0;
}
