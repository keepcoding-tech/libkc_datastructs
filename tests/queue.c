#include "../include/queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the creation and destruction of a queue.
void test_creation_and_destruction() {
  struct Queue queue = new_queue();
  assert(queue.list.head == NULL);
  destroy_queue(&queue);
}

void test_push() {
  // create a new instance of a Queue
  struct Queue queue = new_queue();

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

  destroy_queue(&queue);
}

void test_pop() {
  // create a new instance of a Queue
  struct Queue queue = new_queue();

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

  destroy_queue(&queue);
}

void test_peek() {
  // create a new instance of a Queue
  struct Queue queue = new_queue();

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

  destroy_queue(&queue);
}

int main() {
  test_push();
  test_pop();
  test_peek();
  printf("queue.t .................... OK\n");
  return 0;
}
