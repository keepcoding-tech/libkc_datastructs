#include "../include/queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the creation and destruction of a queue.
void test_creation_and_destruction() {
  struct Queue* queue = new_queue();
  assert(queue->list->head == NULL);
  destroy_queue(queue);
}

void test_push() {
  // create a new instance of a Queue
  struct Queue* queue = new_queue();

  // push ten new nodes of type int
  for (int i = 0; i < 10; ++i) {
    queue->push(queue, &i, sizeof(i));

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

  for (int i = 0; i < 10; ++i) {
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

void test_pop() {
  // create a new instance of a Queue
  struct Queue* queue = new_queue();

  // push ten new nodes (if the test reached here then the "push"
  // function was successfully tested, so we can freely use it)
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

void test_peek() {
  // create a new instance of a Queue
  struct Queue* queue = new_queue();

  // push ten new nodes (if the test reached here then the "push"
  // function was successfully tested, so we can freely use it)
  for (int i = 0; i < 10; ++i) {
    queue->push(queue, &i, sizeof(i));
  }

  for (int i = 0; i < 10; ++i) {
    // check if the nodes have been peeked correctly
    assert(*(int *)queue->peek(queue) == i);

    // destroy the first node (if the test reached here then the "pop"
    // function was successfully tested, so we can freely use it)
    queue->pop(queue);
  }

  destroy_queue(queue);
}

int main() {
  test_creation_and_destruction();
  test_push();
  test_pop();
  test_peek();
  printf("queue.t .................... OK\n");
  return 0;
}
