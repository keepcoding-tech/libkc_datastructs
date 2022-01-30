#include "queue.h"

void queue_tests();

void peek_test();
void pop_test();
void push_test();

void queue_tests() {
  push_test();
  pop_test();
  peek_test();
  printf("queue.t .................... OK\n");
}

// Display where the test failed.
void failed_q(char *test, int line) {
  printf("FAIELD -> %s at line %d\n", test, line);
  exit(1);
}

// Test the "push" function.
void push_test() {
  // create a new instance of a Queue
  struct Queue queue = queue_constructor();

  // push ten new nodes
  for (int i = 0; i < 10; ++i) {
    queue.push(&queue, &i, sizeof(i));
    // check the length of the list
    if (queue.list.length != i + 1) {
      failed_q("push_test", 32);
    }
  }

  for (int i = 0; i < 10; ++i) {
    struct Node *cursor = queue.list.head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been pushed correctly
    if (*(int *)cursor->data != i) {
      failed_q("push_test", 32);
    }
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
    if (queue.list.length != 10 - i) {
      failed_q("pop_test", 85);
    }
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
    if (*(int *)queue.peek(&queue) != i) {
      failed_q("peek_test", 86);
    }

    // destroy the first node (if the test reached here then the "pop"
    // function was successfully tested, so we can freely use it)
    queue.pop(&queue);
  }

  queue_destructor(&queue);
}
