#include "../include/Node.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void node_tests();
void int_data_type();
void char_data_type();
void struct_data_type();

// Test the integer data type.
void int_data_type() {
  // allocate space
  struct Node *node = malloc(sizeof *node);

  // test single integer
  int data = 200;
  *node = node_constructor(&data, sizeof(data));
  assert(*(int *)node->data == 200);

  // test array of integers
  int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  *node = node_constructor(&array, sizeof(array));
  assert(((int *)node->data)[9] == 9);

  node_destructor(node);
}

// Test the character data type.
void char_data_type() {
  // allocate space
  struct Node *node = malloc(sizeof *node);

  // test single character
  char data = 'a';
  *node = node_constructor(&data, sizeof(data));
  assert(*(char *)node->data == 'a');

  // test array of characters
  char array[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
  *node = node_constructor(&array, sizeof(array));

  assert(((char *)node->data)[5] == 'f');
  assert(*(char *)node->data == *(char *)"abc");

  node_destructor(node);
}

// Create a costumized test structure.
struct Test {
  int value;
  char *key;
} test = {200, "test"};

// Test a new structure.
void struct_data_type() {
  // allocate space
  struct Node *node = malloc(sizeof *node);

  *node = node_constructor(&test, sizeof(test));
  struct Test *new_test = node->data;

  // test integer member
  assert(new_test->value == 200);

  // test character member
  assert(strcmp(new_test->key, "test") == 0);

  node_destructor(node);
}

int main() {
  int_data_type();
  char_data_type();
  struct_data_type();
  printf("node.t ..................... OK\n");
  return 0;
}
