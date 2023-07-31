#include "../include/node.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test the creation and destruction of a node.
void test_creation_and_destruction() {
  int data = 10000;
  struct Node* node = node_constructor(&data, sizeof(int));
  assert(*(int*)node->data == data);
  assert(node->next == NULL);
  assert(node->prev == NULL);
  node_destructor(node);
}

// Test the integer (int) data type.
void test_primitive_int() {
  // initialize the node
  int num = 10;
  struct Node* node_int = node_constructor(&num, sizeof(int));

  // verify with a pointer
  int *ptr_int = (int*)node_int->data;
  assert(*ptr_int == num);

  // verify by direct access memory
  assert(*(int *)node_int->data == 10);

  node_destructor(node_int);

  // test the array of integer (int[]) data type
  int nums[] = {1, 2, 3, 4, 5};
  size_t size_int = sizeof(nums) / sizeof(nums[0]);
  struct Node* node_array = node_constructor(nums, sizeof(int) * size_int);

  int* ptr_array = (int*)node_array->data;
  for (size_t i = 0; i < size_int; i++) {
    // verify with a pointer
    assert(ptr_array[i] == nums[i]);

    // verify by direct access memory
    assert(((int *)node_array->data)[i] == nums[i]);
  }

  node_destructor(node_array);
}

// Test the character (char) data type.
void test_primitive_char() {
  // initialize the node
  char letter = 'A';
  struct Node* node_char = node_constructor(&letter, sizeof(char));

  // verify with a pointer
  char *ptr_char = (char*)node_char->data;
  assert(*ptr_char == letter);

  // verify by direct access memory
  assert(*(char *)node_char->data == 'A');

  node_destructor(node_char);

  // test the array of character (char[]) data type
  char letters[] = {'H', 'e', 'l', 'l', 'o'};
  size_t size_char = sizeof(letters) / sizeof(letters[0]);

  struct Node* node_array = node_constructor(letters, sizeof(char) * size_char);

  char *ptr_array = (char *)node_array->data;
  for (size_t i = 0; i < size_char; i++) {
    // verify with a pointer
    assert(ptr_array[i] == letters[i]);

    // verify by direct access memory
    assert(((char *)node_array->data)[i] == letters[i]);
  }

  // test the string (char*) data type
  char* string = "Hello, World!";

  struct Node* node_string = node_constructor(string, strlen(string) + 1);

  char *ptr_string = (char*)node_string->data;
  for (size_t i = 0; i < strlen(string); i++) {
    // verify with a pointer
    assert(ptr_string[i] == string[i]);

    // verify by direct access memory
    assert(((char*)node_string->data)[i] == string[i]);
  }

  node_destructor(node_string);
}

// Test the maximum limit of integer (unsigned long long) data type.
void test_primitive_long() {
  // initialize the node
  unsigned long long data_max = 184467440737095516;
  struct Node* node_max = node_constructor(&data_max, sizeof(data_max));

  // verify with a pointer
  unsigned long long *ptr_max = (unsigned long long *)node_max->data;
  assert(*ptr_max == data_max);

  // verify by direct access memory
  assert(*(unsigned long long *)node_max->data == 184467440737095516);

  node_destructor(node_max);
}


// Test the custom data type (struct).
void test_customized_data_type() {
  // Create a costumized test structure.
  struct Test {
    int key;
    char* value;
  };

  struct Test test = { 100, "test" };

  // initialize and access node data
  struct Node* node = node_constructor(&test, sizeof(struct Test));

  // verify with a pointer
  struct Test *ptr_customized = (struct Test*)node->data;
  assert(ptr_customized->key == test.key);
  assert(strcmp(ptr_customized->value, test.value) == 0);

  // verify by direct access memory
  assert(((struct Test*)node->data)->key == 100);
  assert(strcmp(((struct Test*)node->data)->value, "test") == 0);

  node_destructor(node);
}

int main() {
  test_creation_and_destruction();
  test_primitive_int();
  test_primitive_char();
  test_primitive_long();
  test_customized_data_type();
  printf("node.t ..................... OK\n");
  return 0;
}
