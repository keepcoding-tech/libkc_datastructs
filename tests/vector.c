// This file is part of libkc_datastructs
// ==================================
//
// vector.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../include/vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Test the creation and destruction of a vector.
void test_creation_and_destruction() {
  struct Vector* vector = new_vector();
  assert(vector->length == 0);
  assert(vector->capacity == 16);
  destroy_vector(vector);
}

// Test case for the at() method.
void test_at() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 10 new items
  for (int i = 0; i < 10; ++i) {
    vector->insert(vector, i, &i, sizeof(int));
  }

  // get and verify each element
  for (int i = 0; i < 10; ++i) {
    // check the values of the vector
    assert(*(int*)vector->at(vector, i) == i);
  }

  destroy_vector(vector);
}

// Test case for the back() method.
void test_back() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 10 new items and check the last element
  for (int i = 0; i < 10; ++i) {
    vector->insert(vector, i, &i, sizeof(int));
    assert(*(int*)vector->back(vector) == i);
  }

  destroy_vector(vector);
}

// Test case for the clear() method.
void test_clear() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 20 new items
  for (int i = 0; i < 20; ++i) {
    vector->insert(vector, i, &i, sizeof(int));
  }

  assert(vector->length == 20);
  assert(vector->capacity == 32);

  // clear and check again
  vector->clear(vector);

  assert(vector->length == 0);
  assert(vector->capacity == 16);

  // reuse the freed memory
  vector->data[4] = malloc(sizeof(int));
  *(int*)vector->data[4] = 10;
  assert(*(int*)vector->data[4] == 10);

  destroy_vector(vector);
}

// Test case for the empty() method.
void test_empty() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // the vector should be empty
  assert(vector->empty(vector));

  // push 20 new items
  for (int i = 0; i < 20; ++i) {
    vector->insert(vector, i, &i, sizeof(int));
  }

  // the vector should not be empty
  assert(!vector->empty(vector));

  // the vector should be empty again
  vector->clear(vector);
  assert(vector->empty(vector));

  destroy_vector(vector);
}

// Test case for the erase() method.
void test_erase() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 20 new items
  for (int i = 0; i < 20; ++i) {
    vector->insert(vector, i, &i, sizeof(int));
  }

  // erase the newly created items
  for (int i = 0; i < 10; ++i) {
    vector->erase(vector, 10);

    // check the size
    assert(vector->length == 19 - i);

    // check that all the elements are still in the same order
    for (int j = 10; j < vector->length; ++j) {
      assert(*(int*)vector->data[j] == j + 1 + i);
    }
  }

  // if the length is less than half of the capacity,
  // should resize the max_size to half
  assert(vector->max_size(vector) == 16);

  // erase the last elements
  for (int i = 0; i < 10; ++i) {
    vector->erase(vector, 0);
  }

  assert(vector->max_size(vector) == 16);
  assert(vector->empty(vector));

  destroy_vector(vector);
}

// Test case for the front() method.
void test_front() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 10 new items and check the last element
  for (int i = 0; i < 10; ++i) {
    vector->insert(vector, 0, &i, sizeof(int));
    assert(*(int*)vector->front(vector) == i);
  }

  destroy_vector(vector);
}

// Test case for the insert() method.
void test_insert() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 20 new items
  for (int i = 0; i < 20; ++i) {
    vector->insert(vector, i, &i, sizeof(int));

    // check the size of the vector
    assert(vector->length == i + 1);

    // check the values of the vector
    assert(*(int*)vector->data[i] == i);
  }

  // check the capacity of the vector
  assert(vector->capacity == 32);

  int data = 100;
  vector->insert(vector, 10, &data, sizeof(int));
  vector->insert(vector, 11, &data, sizeof(int));
  vector->insert(vector, 12, &data, sizeof(int));

  // check the values of the vector
  assert(*(int*)vector->data[10] == 100);
  assert(*(int*)vector->data[11] == 100);
  assert(*(int*)vector->data[12] == 100);

  destroy_vector(vector);
}

// Test case for the max_size() method.
void test_max_size() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // check the capacity of the vector
  assert(vector->capacity == vector->max_size(vector));
  assert(vector->max_size(vector) == 16);

  // push 20 new items
  for (int i = 0; i < 20; ++i) {
    vector->insert(vector, i, &i, sizeof(int));

    // check the capacity of the vector
    if (i < 15) {
      assert(vector->max_size(vector) == 16);
      continue;
    }

    assert(vector->max_size(vector) == 32);
  }

  // check the capacity of the vector
  assert(vector->capacity == vector->max_size(vector));
  assert(vector->max_size(vector) == 32);

  destroy_vector(vector);
}

// Test case for the pop_back() method.
void test_pop_back() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 15 new items
  for (int i = 0; i < 15; ++i) {
    vector->insert(vector, i, &i, sizeof(int));
  }

  // erase the last elements
  for (int i = 0; i < 15; ++i) {
    // check the last element before poping
    assert(vector->length == 15 - i);
    assert(*(int*)vector->back(vector) == 14 - i);

    vector->pop_back(vector);
  }

  destroy_vector(vector);
}

// Test case for the pop_front() method.
void test_pop_front() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 15 new items
  for (int i = 0; i < 15; ++i) {
    vector->insert(vector, i, &i, sizeof(int));
  }

  // erase the first elements
  for (int i = 0; i < 15; ++i) {
    // check the first element before poping
    assert(vector->length == 15 - i);
    assert(*(int*)vector->front(vector) == i);

    vector->pop_front(vector);
  }

  destroy_vector(vector);
}

// Test case for the push_back() method.
void test_push_back() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  for (int i = 0; i < 10; ++i) {
    vector->push_back(vector, &i, sizeof(int));

    // check the length and the data inserted
    assert(vector->length == i + 1);
    assert(*(int*)vector->at(vector, vector->length - 1) == i);
  }

  destroy_vector(vector);
}

// Test case for the push_front() method.
void test_push_front() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  for (int i = 0; i < 10; ++i) {
    vector->push_front(vector, &i, sizeof(int));

    // check the length and the data inserted
    assert(vector->length == i + 1);
    assert(*(int*)vector->at(vector, 0) == i);
  }

  destroy_vector(vector);
}

// Test case for the remove() method.
int compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

// Test case for the remove() method.
void test_remove() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // add 5 new elements
  int data = 10;
  for (int i = 0; i < 5; ++i) {
    vector->push_back(vector, &data, sizeof(int));
  }

  // add 5 more new elements
  data = 20;
  for (int i = 0; i < 5; ++i) {
    vector->push_back(vector, &data, sizeof(int));
  }

  // should remove only 5 elements
  vector->remove(vector, &data, compare);
  assert(vector->length == 5);

  data = 10;

  // should remove all 5 elements
  vector->remove(vector, &data, compare);
  assert(vector->empty(vector));

  destroy_vector(vector);
}

// Test case for the resize() method.
void test_resize() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // check the default capacity size
  assert(vector->max_size(vector) == 16);

  // change the capacity and check it
  vector->resize(vector, 64);
  assert(vector->max_size(vector) == 64);
  vector->resize(vector, 128);
  assert(vector->max_size(vector) == 128);
  vector->resize(vector, 16);
  assert(vector->max_size(vector) == 16);

  destroy_vector(vector);
}

// Test case for the search() method.
void test_search() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // add 10 new elements
  for (int i = 0; i < 10; ++i) {
    vector->push_back(vector, &i, sizeof(int));
  }

  // should return true
  int search_data = 3;
  assert(vector->search(vector, &search_data, compare) == true);

  // should return true
  search_data = 8;
  assert(vector->search(vector, &search_data, compare) == true);

  // should return false
  search_data = 12;
  assert(vector->search(vector, &search_data, compare) == false);

  destroy_vector(vector);
}

// Test case for all data types.
void test_all_data_types() {
  struct Vector* vector = new_vector();

  // test integer (int)
  int intValue = 42;
  vector->insert(vector, vector->length, &intValue, sizeof(int));
  assert(*(int*)vector->data[0] == 42);

  // test real (double)
  double doubleValue = 3.14;
  vector->insert(vector, vector->length, &doubleValue, sizeof(double));
  assert(*(double*)vector->data[1] == 3.14);

  // test character (char)
  char stringValue[] = "Hello, World!";
  vector->insert(vector, vector->length, stringValue, sizeof(stringValue));
  assert(strcmp((char*)vector->data[2], "Hello, World!") == 0);

  // test custom data ()struct)
  struct Test { int key; char* val; } test = {10, "test"};
  vector->insert(vector, vector->length, &test, sizeof(struct Test));
  struct Test *ptr = (struct Test*)vector->data[3];
  assert(strcmp(ptr->val, test.val) == 0);
  assert(ptr->key == test.key);

  destroy_vector(vector);
}

int main() {
  test_creation_and_destruction();
  test_at();
  test_back();
  test_clear();
  test_empty();
  test_erase();
  test_front();
  test_insert();
  test_max_size();
  test_pop_back();
  test_pop_front();
  test_push_back();
  test_push_front();
  test_remove();
  test_resize();
  test_search();
  test_all_data_types();
  printf("vector.t ................... OK\n");
  return 0;
}
