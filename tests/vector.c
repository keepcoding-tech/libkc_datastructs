#include "../include/vector.h"

#include <assert.h>
#include <string.h>

// Test the creation and destruction of a vector.
void test_creation_and_destruction() {
  struct Vector* vector = new_vector();
  assert(vector->size == 0);
  destroy_vector(vector);
}

// Test case for the push() method.
void test_push() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 20 new items
  for (int i = 0; i < 20; ++i) {
    vector->push(vector, &i, sizeof(int));

    // check the size of the vector
    assert(vector->size == i + 1);

    // check the values of the vector
    assert(*(int*)vector->data[i] == i);
  }

  // check the capacity of the vector
  assert(vector->capacity == 32);

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
    vector->push(vector, &i, sizeof(int));

    // check the capacity of the vector
    if (i < 16) {
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

// Test case for the erase() method.
void test_erase() {
  // create a new instance of a List
  struct Vector* vector = new_vector();

  // push 20 new items
  for (int i = 0; i < 20; ++i) {
    vector->push(vector, &i, sizeof(int));
  }

  // erase the newly created items
  for (int i = 0; i < 10; ++i) {
    vector->erase(vector, 10);

    // check the size
    assert(vector->size == 19 - i);

    // check that all the elements are still in the same order
    for (int j = 10; j < vector->size; ++j) {
      assert(*(int*)vector->data[j] == j + 1 + i);
    }
  }

  destroy_vector(vector);
}

// Test case for all data types.
void test_all_data_types() {
  struct Vector* vector = new_vector();

  // test integer (int)
  int intValue = 42;
  vector->push(vector, &intValue, sizeof(int));
  assert(*(int*)vector->data[0] == 42);

  // test real (double)
  double doubleValue = 3.14;
  vector->push(vector, &doubleValue, sizeof(double));
  assert(*(double*)vector->data[1] == 3.14);

  // test character (char)
  char stringValue[] = "Hello, World!";
  vector->push(vector, stringValue, sizeof(stringValue));
  assert(strcmp((char*)vector->data[2], "Hello, World!") == 0);

  // test custom data ()struct)
  struct Test { int key; char* val; } test = {10, "test"};
  vector->push(vector, &test, sizeof(struct Test));
  struct Test *ptr = (struct Test*)vector->data[3];
  assert(strcmp(ptr->val, test.val) == 0);
  assert(ptr->key == test.key);

  destroy_vector(vector);
}

int main() {
  test_creation_and_destruction();
  test_push();
  test_max_size();
  test_erase();
  test_all_data_types();
  printf("vector.t ................... OK\n");
  return 0;
}
