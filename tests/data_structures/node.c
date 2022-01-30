#include <stdio.h>
#include <stdlib.h>

#include "../../data_structures/utils/Node.h"

void node_tests();

void int_data_type();
void char_data_type();
void struct_data_type();

void node_tests() {
  int_data_type();
  char_data_type();
  struct_data_type();
  printf("node.t ..................... OK\n");
}

// Display where the test failed.
void failed(char *test, int line) {
  printf("FAIELD -> %s at line %d\n", test, line);
  exit(1);
}

// Test the integer data type.
void int_data_type() {
  // allocate space
  struct Node *node = malloc(sizeof *node);

  // test single integer
  int data = 200;
  *node = node_constructor(&data, sizeof(data));
  if (*(int *)node->data != 200) {
    failed("int_data_type", 34);
  }

  // test array of integers
  int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  *node = node_constructor(&array, sizeof(array));
  if (((int *)node->data)[9] != 9) {
    failed("int_data_type", 41);
  }

  node_destructor(node);
}

// Test the character data type.
void char_data_type() {
  // allocate space
  struct Node *node = malloc(sizeof *node);

  // test single character
  char data = 'a';
  *node = node_constructor(&data, sizeof(data));
  if (*(char *)node->data != 'a') {
    failed("char_data_type", 56);
  }

  // test array of characters
  char array[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
  *node = node_constructor(&array, sizeof(array));

  if (((char *)node->data)[5] != 'f') {
    failed("char_data_type", 64);
  } else if (*(char *)node->data != *(char *)"abc") {
    failed("char_data_type", 66);
  }

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
  if (new_test->value != 200) {
    failed("struct_data_type", 88);
  }

  // test character member
  if (new_test->key != "test") {
    failed("struct_data_type", 93);
  }

  node_destructor(node);
}
