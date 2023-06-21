#include "../include/node.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void primitive_data_types() {
  // test the integer (int) data type
  int data_int = 10;

  struct Node* node_int = malloc(sizeof *node_int);
  node_int = node_constructor(&data_int, sizeof(data_int));

  // verify with a pointer
  int *ptr_int = (int *)node_int->data;
  assert(*ptr_int == data_int);

  // verify by direct access memory
  assert(*(int *)node_int->data == 10);

  node_destructor(node_int);

  // test the array of integer (int[]) data type
  int data_int_array[] = {1, 2, 3, 4, 5};
  size_t size_int = sizeof(data_int_array) / sizeof(data_int_array[0]);

  struct Node* node_int_array = malloc(sizeof *node_int_array);
  node_int_array = node_constructor(data_int_array, sizeof(int) * size_int);

  int *ptr_int_array = (int *)node_int_array->data;
  for (size_t i = 0; i < size_int; i++) {
    // verify with a pointer
    assert(ptr_int_array[i] == data_int_array[i]);

    // verify by direct access memory
    assert(((int *)node_int_array->data)[i] == data_int_array[i]);
  }

  node_destructor(node_int_array);

  // test the character (char) data type
  char data_char = 'A';

  struct Node* node_char = malloc(sizeof *node_char);
  node_char = node_constructor(&data_char, sizeof(data_char));

  // verify with a pointer
  char *ptr_char = (char *)node_char->data;
  assert(*ptr_char == data_char);

  // verify by direct access memory
  assert(*(char *)node_char->data == 'A');

  node_destructor(node_char);

  // test the array of character (char[]) data type
  char data_char_array[] = {'H', 'e', 'l', 'l', 'o'};
  size_t size_char = sizeof(data_char_array) / sizeof(data_char_array[0]);

  struct Node* node_char_array = malloc(sizeof *node_char_array);
  node_char_array = node_constructor(data_char_array, sizeof(int) * size_char);

  char *ptr_char_array = (char *)node_char_array->data;
  for (size_t i = 0; i < size_char; i++) {
    // verify with a pointer
    assert(ptr_char_array[i] == data_char_array[i]);

    // verify by direct access memory
    assert(((char *)node_char_array->data)[i] == data_char_array[i]);
  }

  node_destructor(node_char_array);

  // test the maximum limit of integer (unsigned long long) data type
  unsigned long long data_max = 184467440737095516;

  struct Node* node_max = malloc(sizeof *node_max);
  node_max = node_constructor(&data_max, sizeof(data_max));

  // verify with a pointer
  unsigned long long *ptr_max = (unsigned long long *)node_max->data;
  assert(*ptr_max == data_max);

  // verify by direct access memory
  assert(*(unsigned long long *)node_max->data == 184467440737095516);

  node_destructor(node_max);
}

// Create a costumized test structure.
struct Test {
  int value;
  char *key;
};

void customized_data_type() {
  struct Test data_customized = { 200, "test" };

  struct Node* node = malloc(sizeof *node);
  node = node_constructor(&data_customized, sizeof(data_customized));

  // verify with a pointer
  struct Test *ptr_customized = (struct Test *)node->data;
  assert(strcmp(ptr_customized->key, data_customized.key) == 0);
  assert(ptr_customized->value == data_customized.value);

  node_destructor(node);
}

int main() {
  primitive_data_types();
  customized_data_type();
  printf("node.t ..................... OK\n");
  return 0;
}
