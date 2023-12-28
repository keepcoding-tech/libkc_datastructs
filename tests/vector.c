// This file is part of libkc_datastructs
// ==================================
//
// vector.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc/testing/testing.h"
#include "../include/vector.h"

#include <stdlib.h>
#include <string.h>

// Test case for the remove() method.
int compare(const void* a, const void* b)
{
  return (*(int*)a - *(int*)b);
}

int main() {
  testgroup("Vector")
  {
    subtest("test creation and destruction")
    {
      struct Vector* vector = new_vector();
      ok(vector->length == 0);
      ok(vector->capacity == 16);
      destroy_vector(vector);
    }

    subtest("test at")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 10 new items
      for (int i = 0; i < 10; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));
      }

      // get and verify each element
      for (int i = 0; i < 10; ++i)
      {
        // check the values of the vector
        ok(*(int*)vector->at(vector, i) == i);
      }

      destroy_vector(vector);
    }

    subtest("test back")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 10 new items and check the last element
      for (int i = 0; i < 10; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));
        ok(*(int*)vector->back(vector) == i);
      }

      destroy_vector(vector);
    }

    subtest("test clear")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));
      }

      ok(vector->length == 20);
      ok(vector->capacity == 32);

      // clear and check again
      vector->clear(vector);

      ok(vector->length == 0);
      ok(vector->capacity == 16);

      // reuse the freed memory
      vector->data[4] = malloc(sizeof(int));
      *(int*)vector->data[4] = 10;
      ok(*(int*)vector->data[4] == 10);

      destroy_vector(vector);
    }

    subtest("test empty")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // the vector should be empty
      ok(vector->empty(vector));

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));
      }

      // the vector should not be empty
      ok(!vector->empty(vector));

      // the vector should be empty again
      vector->clear(vector);
      ok(vector->empty(vector));

      destroy_vector(vector);
    }

    subtest("test erase")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));
      }

      // erase the newly created items
      for (int i = 0; i < 10; ++i)
      {
        vector->erase(vector, 10);

        // check the size
        ok(vector->length == 19 - i);

        // check that all the elements are still in the same order
        for (int j = 10; j < vector->length; ++j)
        {
          ok(*(int*)vector->data[j] == j + 1 + i);
        }
      }

      // if the length is less than half of the capacity,
      // should resize the max_size to half
      ok(vector->max_size(vector) == 16);

      // erase the last elements
      for (int i = 0; i < 10; ++i)
      {
        vector->erase(vector, 0);
      }

      ok(vector->max_size(vector) == 16);
      ok(vector->empty(vector));

      destroy_vector(vector);
    }

    subtest("test front")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 10 new items and check the last element
      for (int i = 0; i < 10; ++i)
      {
        vector->insert(vector, 0, &i, sizeof(int));
        ok(*(int*)vector->front(vector) == i);
      }

      destroy_vector(vector);
    }

    subtest("test insert")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));

        // check the size of the vector
        ok(vector->length == i + 1);

        // check the values of the vector
        ok(*(int*)vector->data[i] == i);
      }

      // check the capacity of the vector
      ok(vector->capacity == 32);

      int data = 100;
      vector->insert(vector, 10, &data, sizeof(int));
      vector->insert(vector, 11, &data, sizeof(int));
      vector->insert(vector, 12, &data, sizeof(int));

      // check the values of the vector
      ok(*(int*)vector->data[10] == 100);
      ok(*(int*)vector->data[11] == 100);
      ok(*(int*)vector->data[12] == 100);

      destroy_vector(vector);
    }

    subtest("test max size")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // check the capacity of the vector
      ok(vector->capacity == vector->max_size(vector));
      ok(vector->max_size(vector) == 16);

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));

        // check the capacity of the vector
        if (i < 15) {
          ok(vector->max_size(vector) == 16);
          continue;
        }

        ok(vector->max_size(vector) == 32);
      }

      // check the capacity of the vector
      ok(vector->capacity == vector->max_size(vector));
      ok(vector->max_size(vector) == 32);

      destroy_vector(vector);
    }

    subtest("test pop back")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 15 new items
      for (int i = 0; i < 15; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));
      }

      // erase the last elements
      for (int i = 0; i < 15; ++i)
      {
        // check the last element before poping
        ok(vector->length == 15 - i);
        ok(*(int*)vector->back(vector) == 14 - i);

        vector->pop_back(vector);
      }

      destroy_vector(vector);
    }

    subtest("test pop front")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // push 15 new items
      for (int i = 0; i < 15; ++i)
      {
        vector->insert(vector, i, &i, sizeof(int));
      }

      // erase the first elements
      for (int i = 0; i < 15; ++i)
      {
        // check the first element before poping
        ok(vector->length == 15 - i);
        ok(*(int*)vector->front(vector) == i);

        vector->pop_front(vector);
      }

      destroy_vector(vector);
    }

    subtest("test push back")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      for (int i = 0; i < 10; ++i)
      {
        vector->push_back(vector, &i, sizeof(int));

        // check the length and the data inserted
        ok(vector->length == i + 1);
        ok(*(int*)vector->at(vector, vector->length - 1) == i);
      }

      destroy_vector(vector);
    }

    subtest("test push front")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      for (int i = 0; i < 10; ++i)
      {
        vector->push_front(vector, &i, sizeof(int));

        // check the length and the data inserted
        ok(vector->length == i + 1);
        ok(*(int*)vector->at(vector, 0) == i);
      }

      destroy_vector(vector);
    }

    subtest("test remove")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // add 5 new elements
      int data = 10;
      for (int i = 0; i < 5; ++i)
      {
        vector->push_back(vector, &data, sizeof(int));
      }

      // add 5 more new elements
      data = 20;
      for (int i = 0; i < 5; ++i)
      {
        vector->push_back(vector, &data, sizeof(int));
      }

      // should remove only 5 elements
      vector->remove(vector, &data, compare);
      ok(vector->length == 5);

      data = 10;

      // should remove all 5 elements
      vector->remove(vector, &data, compare);
      ok(vector->empty(vector));

      destroy_vector(vector);
    }

    subtest("test resize")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // check the default capacity size
      ok(vector->max_size(vector) == 16);

      // change the capacity and check it
      vector->resize(vector, 64);
      ok(vector->max_size(vector) == 64);
      vector->resize(vector, 128);
      ok(vector->max_size(vector) == 128);
      vector->resize(vector, 16);
      ok(vector->max_size(vector) == 16);

      destroy_vector(vector);
    }

    subtest("test search")
    {
      // create a new instance of a List
      struct Vector* vector = new_vector();

      // add 10 new elements
      for (int i = 0; i < 10; ++i) {
        vector->push_back(vector, &i, sizeof(int));
      }

      // should return true
      int search_data = 3;
      ok(vector->search(vector, &search_data, compare) == true);

      // should return true
      search_data = 8;
      ok(vector->search(vector, &search_data, compare) == true);

      // should return false
      search_data = 12;
      ok(vector->search(vector, &search_data, compare) == false);

      destroy_vector(vector);
    }

    subtest("test all data types")
    {
      struct Vector* vector = new_vector();

      // test integer (int)
      int intValue = 42;
      vector->insert(vector, vector->length, &intValue, sizeof(int));
      ok(*(int*)vector->data[0] == 42);

      // test real (double)
      double doubleValue = 3.14;
      vector->insert(vector, vector->length, &doubleValue, sizeof(double));
      ok(*(double*)vector->data[1] == 3.14);

      // test character (char)
      char stringValue[] = "Hello, World!";
      vector->insert(vector, vector->length, stringValue, sizeof(stringValue));
      ok(strcmp((char*)vector->data[2], "Hello, World!") == 0);

      // test custom data ()struct)
      struct Test { int key; char* val; } test = { 10, "test" };
      vector->insert(vector, vector->length, &test, sizeof(struct Test));
      struct Test* ptr = (struct Test*)vector->data[3];
      ok(strcmp(ptr->val, test.val) == 0);
      ok(ptr->key == test.key);

      destroy_vector(vector);
    }

    done_testing()
  }

  return 0;
}
