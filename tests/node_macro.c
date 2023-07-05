#include "../include/node.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>

NODE(_Bool)
NODE(char)
NODE(short)
NODE(int)
NODE(long)
NODE(int8_t)
NODE(uint8_t)
NODE(int16_t)
NODE(uint16_t)
NODE(int32_t)
NODE(uint32_t)
NODE(int64_t)
NODE(uint64_t)
NODE(float)
NODE(double)

void test__Bool() {
  // check if the data is inserted correctly
  struct Node__Bool* node = node__Bool(true);
  assert(node->data == true);

  // check if the data is changed correctly
  node->data = false;
  assert(node->data == false);

  node_destructor__Bool(node);
}

void test_char() {
  // check if the data is inserted correctly
  struct Node_char* node = node_char('A');
  assert(node->data == 'A');

  // check if the data is changed correctly
  node->data = 'B';
  assert(node->data == 'B');

  node_destructor_char(node);
}

void test_short() {
  // check if the data is inserted correctly
  struct Node_short* node = node_short(42);
  assert(node->data == 42);

  // check if the data is changed correctly
  node->data = 99;
  assert(node->data == 99);

  node_destructor_short(node);
}

void test_int() {
  // check if the data is inserted correctly
  struct Node_int* node = node_int(123);
  assert(node->data == 123);

  // check if the data is changed correctly
  node->data = 456;
  assert(node->data == 456);

  node_destructor_int(node);
}

void test_long() {
  // check if the data is inserted correctly
  struct Node_long* node = node_long(987654321);
  assert(node->data == 987654321);

  // check if the data is changed correctly
  node->data = 123456789;
  assert(node->data == 123456789);

  node_destructor_long(node);
}

void test_int8_t() {
  // check if the data is inserted correctly
  struct Node_int8_t* node = node_int8_t(10);
  assert(node->data == 10);

  // check if the data is changed correctly
  node->data = -5;
  assert(node->data == -5);

  node_destructor_int8_t(node);
}

void test_uint8_t() {
  // check if the data is inserted correctly
  struct Node_uint8_t* node = node_uint8_t(200);
  assert(node->data == 200);

  // check if the data is changed correctly
  node->data = 150;
  assert(node->data == 150);

  node_destructor_uint8_t(node);
}

void test_int16_t() {
  // check if the data is inserted correctly
  struct Node_int16_t* node = node_int16_t(-1000);
  assert(node->data == -1000);

  // check if the data is changed correctly
  node->data = -500;
  assert(node->data == -500);

  node_destructor_int16_t(node);
}

void test_uint16_t() {
  // check if the data is inserted correctly
  struct Node_uint16_t* node = node_uint16_t(5000);
  assert(node->data == 5000);

  // check if the data is changed correctly
  node->data = 10000;
  assert(node->data == 10000);

  node_destructor_uint16_t(node);
}

void test_int32_t() {
  // check if the data is inserted correctly
  struct Node_int32_t* node = node_int32_t(-1000000);
  assert(node->data == -1000000);

  // check if the data is changed correctly
  node->data = -500000;
  assert(node->data == -500000);

  node_destructor_int32_t(node);
}

void test_uint32_t() {
  // check if the data is inserted correctly
  struct Node_uint32_t* node = node_uint32_t(2000000);
  assert(node->data == 2000000);

  // check if the data is changed correctly
  node->data = 3000000;
  assert(node->data == 3000000);

  node_destructor_uint32_t(node);
}

void test_int64_t() {
  // check if the data is inserted correctly
  struct Node_int64_t* node = node_int64_t(-1000000000);
  assert(node->data == -1000000000);

  // check if the data is changed correctly
  node->data = -500000000;
  assert(node->data == -500000000);

  node_destructor_int64_t(node);
}

void test_uint64_t() {
  // check if the data is inserted correctly
  struct Node_uint64_t* node = node_uint64_t(2000000000);
  assert(node->data == 2000000000);

  // check if the data is changed correctly
  node->data = 3000000000;
  assert(node->data == 3000000000);

  node_destructor_uint64_t(node);
}

void test_float() {
  // check if the data is inserted correctly
  struct Node_float* node = node_float(3.14f);
  assert(node->data == 3.14f);

  // check if the data is changed correctly
  node->data = 2.71f;
  assert(node->data == 2.71f);

  node_destructor_float(node);
}

void test_double() {
  // check if the data is inserted correctly
  struct Node_double* node = node_double(3.14159);
  assert(node->data == 3.14159);

  // check if the data is changed correctly
  node->data = 2.71828;
  assert(node->data == 2.71828);

  node_destructor_double(node);
}


int main() {
  test__Bool();
  test_char();
  test_short();
  test_int();
  test_long();
  test_int8_t();
  test_uint8_t();
  test_int16_t();
  test_uint16_t();
  test_int32_t();
  test_uint32_t();
  test_int64_t();
  test_uint64_t();
  test_float();
  test_double();
  printf("node_macro.t ............... OK\n");
  return 0;
}

