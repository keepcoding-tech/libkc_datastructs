#include "../include/queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test the creation and destruction of a queue.
void test_creation_and_destruction() {
  struct Queue* queue = new_queue();
  assert(queue->list->head == NULL);
  destroy_queue(queue);
}

// Test case for the length() method.
void test_length() {
  // create a new instance of a Queue
  struct Queue* queue = new_queue();

  // the list should be empty
  assert(queue->length(queue) == 0);

  // push ten new nodes
  for (int i = 0; i < 10; ++i) {
    queue->push(queue, &i, sizeof(i));
  }

  // the list should be have 10 nodes
  assert(queue->length(queue) == 10);

  // remove 4 nodes
  queue->pop(queue);
  queue->pop(queue);
  queue->pop(queue);
  queue->pop(queue);

  // the list should be have 6 nodes
  assert(queue->length(queue) == 6);

  destroy_queue(queue);
}

// Test case for the peek() method.
void test_peek() {
  // create a new instance of a Queue
  struct Queue* queue = new_queue();

  // push ten new nodes
  for (int i = 0; i < 10; ++i) {
    queue->push(queue, &i, sizeof(i));
  }

  for (int i = 0; i < 10; ++i) {
    // check if the nodes have been peeked correctly
    assert(*(int *)queue->peek(queue) == i);

    // destroy the first node
    queue->pop(queue);
  }

  destroy_queue(queue);
}

// Test case for the pop() method.
void test_pop() {
  // create a new instance of a Queue
  struct Queue* queue = new_queue();

  // push ten new nodes
  for (int i = 0; i < 10; ++i) {
    queue->push(queue, &i, sizeof(i));
  }

  for (int i = 1; i < 10; ++i) {
    queue->pop(queue);

    // check if the nodes have been removed correctly
    assert(queue->list->length == 10 - i);
  }

  destroy_queue(queue);
}

// Test case for the push() method.
void test_push() {
  // create a new instance of a Queue
  struct Queue* queue = new_queue();

  // push ten new nodes of type int
  for (int i = 0; i < 10; ++i) {
    queue->push(queue, &i, sizeof(int));

    // check the length of the list
    assert(queue->list->length == i + 1);
  }

  // push ten new nodes of type char
  for (int i = 10; i < 20; ++i) {
    char c = 'a' + i;
    queue->push(queue, &c, sizeof(char));

    // check the length of the list
    assert(queue->list->length == i + 1);
  }

  for (int i = 0; i < 20; ++i) {
    struct Node* cursor = queue->list->head;
    for (int j = 0; j < i; ++j) {
      cursor = cursor->next;
    }

    // check if the nodes have been inserted correctly
    if (i < 10) {
      assert(*(int*)cursor->data == i);
    } else {
      assert(*(char*)cursor->data == 'a' + i);
    }
  }

  // add a new node of type int[] (array)
  int nums[] = {1, 2, 3, 4, 5};
  size_t size = sizeof(nums) / sizeof(nums[0]);
  queue->push(queue, &nums, sizeof(int) * size);

  // get the 21st node
  struct Node* cursor = queue->list->tail;

  // check if the node has been inserted correctly
  int* ptr = (int*)cursor->data;
  for (int i = 0; i < size; ++i) {
    assert(ptr[i] == nums[i]);
  }

  // add a new node of type Test (struct)
  struct Test {
    int key;
    char* value;
  };

  struct Test test = { 100, "example" };
  queue->push(queue, &test, sizeof(struct Test));

  // get the 22st node
  cursor = queue->list->tail;

  assert((int)(((struct Test*)cursor->data)->key) == test.key);
  assert(strcmp((char*)(((struct Test*)cursor->data)->value), test.value) == 0);

  destroy_queue(queue);
}

int main() {
  test_creation_and_destruction();
  test_length();
  test_peek();
  test_pop();
  test_push();
  printf("queue.t .................... OK\n");
  return 0;
}
