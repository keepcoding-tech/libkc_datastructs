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
  struct Node__Bool* node = node__Bool(true);
  assert(node->data == true);
  node_destructor__Bool(node);
}

void test_char() {
  struct Node_char* node = node_char('A');
  assert(node->data == 'A');
  node_destructor_char(node);
}

void test_short() {
  struct Node_short* node = node_short(42);
  assert(node->data == 42);
  node_destructor_short(node);
}

void test_int() {
  struct Node_int* node = node_int(123);
  assert(node->data == 123);
  node_destructor_int(node);
}

void test_long() {
  struct Node_long* node = node_long(1234567890L);
  assert(node->data == 1234567890L);
  node_destructor_long(node);
}

void test_int8_t() {
  struct Node_int8_t* node = node_int8_t(-50);
  assert(node->data == -50);
  node_destructor_int8_t(node);
}

void test_uint8_t() {
  struct Node_uint8_t* node = node_uint8_t(200);
  assert(node->data == 200);
  node_destructor_uint8_t(node);
}

void test_int16_t() {
  struct Node_int16_t* node = node_int16_t(-1000);
  assert(node->data == -1000);
  node_destructor_int16_t(node);
}

void test_uint16_t() {
  struct Node_uint16_t* node = node_uint16_t(5000);
  assert(node->data == 5000);
  node_destructor_uint16_t(node);
}

void test_int32_t() {
  struct Node_int32_t* node = node_int32_t(-1000000);
  assert(node->data == -1000000);
  node_destructor_int32_t(node);
}

void test_uint32_t() {
  struct Node_uint32_t* node = node_uint32_t(2000000);
  assert(node->data == 2000000);
  node_destructor_uint32_t(node);
}

void test_int64_t() {
  struct Node_int64_t* node = node_int64_t(-1000000000);
  assert(node->data == -1000000000);
  node_destructor_int64_t(node);
}

void test_uint64_t() {
  struct Node_uint64_t* node = node_uint64_t(2000000000);
  assert(node->data == 2000000000);
  node_destructor_uint64_t(node);
}

void test_float() {
  struct Node_float* node = node_float(3.14f);
  assert(node->data == 3.14f);
  node_destructor_float(node);
}

void test_double() {
  struct Node_double* node = node_double(3.14159);
  assert(node->data == 3.14159);
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

