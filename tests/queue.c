// This file is part of libkc_datastructs
// ==================================
//
// queue.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc/testing/testing.h"
#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  testgroup("Queue")
  {
    subtest("test creation and destruction")
    {
      struct Queue* queue = new_queue();
      ok(queue->list->head == NULL);
      destroy_queue(queue);
    }

    subtest("test length")
    {
      // create a new instance of a Queue
      struct Queue* queue = new_queue();

      // the list should be empty
      ok(queue->length(queue) == 0);

      // push ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        queue->push(queue, &i, sizeof(i));
      }

      // the list should be have 10 nodes
      ok(queue->length(queue) == 10);

      // remove 4 nodes
      queue->pop(queue);
      queue->pop(queue);
      queue->pop(queue);
      queue->pop(queue);

      // the list should be have 6 nodes
      ok(queue->length(queue) == 6);

      destroy_queue(queue);
    }

    subtest("test peek")
    {
      // create a new instance of a Queue
      struct Queue* queue = new_queue();

      // push ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        queue->push(queue, &i, sizeof(i));
      }

      for (int i = 0; i < 10; ++i)
      {
        // check if the nodes have been peeked correctly
        ok(*(int*)queue->peek(queue) == i);

        // destroy the first node
        queue->pop(queue);
      }

      destroy_queue(queue);
    }

    subtest("test pop")
    {
      // create a new instance of a Queue
      struct Queue* queue = new_queue();

      // push ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        queue->push(queue, &i, sizeof(i));
      }

      for (int i = 1; i < 10; ++i)
      {
        queue->pop(queue);

        // check if the nodes have been removed correctly
        ok(queue->list->length == 10 - i);
      }

      destroy_queue(queue);
    }

    subtest("test push")
    {
      // create a new instance of a Queue
      struct Queue* queue = new_queue();

      // push ten new nodes of type int
      for (int i = 0; i < 10; ++i)
      {
        queue->push(queue, &i, sizeof(int));

        // check the length of the list
        ok(queue->list->length == i + 1);
      }

      // push ten new nodes of type char
      for (int i = 10; i < 20; ++i)
      {
        char c = 'a' + i;
        queue->push(queue, &c, sizeof(char));

        // check the length of the list
        ok(queue->list->length == i + 1);
      }

      for (int i = 0; i < 20; ++i)
      {
        struct Node* cursor = queue->list->head;
        for (int j = 0; j < i; ++j)
        {
          cursor = cursor->next;
        }

        // check if the nodes have been inserted correctly
        if (i < 10)
        {
          ok(*(int*)cursor->data == i);
        }
        else
        {
          ok(*(char*)cursor->data == 'a' + i);
        }
      }

      // add a new node of type int[] (array)
      int nums[] = { 1, 2, 3, 4, 5 };
      size_t size = sizeof(nums) / sizeof(nums[0]);
      queue->push(queue, &nums, sizeof(int) * size);

      // get the 21st node
      struct Node* cursor = queue->list->tail;

      // check if the node has been inserted correctly
      int* ptr = (int*)cursor->data;
      for (int i = 0; i < size; ++i)
      {
        ok(ptr[i] == nums[i]);
      }

      // add a new node of type Test (struct)
      struct Test
      {
        int key;
        char* value;
      };

      struct Test test = { 100, "example" };
      queue->push(queue, &test, sizeof(struct Test));

      // get the 22st node
      cursor = queue->list->tail;

      ok((int)(((struct Test*)cursor->data)->key) == test.key);
      ok(strcmp((char*)(((struct Test*)cursor->data)->value), test.value) == 0);

      destroy_queue(queue);
    }

    done_testing()
  }

  return 0;
}
