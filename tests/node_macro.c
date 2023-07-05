#include "../include/node.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>

CUSTOM_NODE(long double, Node_long_double)
CUSTOM_NODE(signed char, Node_signed_char)
CUSTOM_NODE(unsigned char, Node_unsigned_char)
CUSTOM_NODE(unsigned short, Node_unsigned_short)
CUSTOM_NODE(unsigned int, Node_unsigned_int)
CUSTOM_NODE(unsigned long, Node_unsigned_long)
CUSTOM_NODE(long long, Node_long_long)
CUSTOM_NODE(unsigned long long, Node_unsigned_long_long)

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
NODE(int_least8_t)
NODE(uint_least8_t)
NODE(int_least16_t)
NODE(uint_least16_t)
NODE(int_least32_t)
NODE(uint_least32_t)
NODE(int_least64_t)
NODE(uint_least64_t)
NODE(int_fast8_t)
NODE(uint_fast8_t)
NODE(int_fast16_t)
NODE(uint_fast16_t)
NODE(int_fast32_t)
NODE(uint_fast32_t)
NODE(int_fast64_t)
NODE(uint_fast64_t)
NODE(intptr_t)
NODE(uintptr_t)
NODE(intmax_t)
NODE(uintmax_t)
NODE(float)
NODE(double)
NODE(_Bool)

void test_long_double() {
  struct Node_long_double* node = Node_long_double_constructor(1.23);
  assert(node->data == 1.23);

  node->data = 4.56;
  assert(node->data == 4.56);

  Node_long_double_destructor(node);
}

void test_signed_char() {
  struct Node_signed_char* node = Node_signed_char_constructor('a');
  assert(node->data == 'a');

  node->data = 'b';
  assert(node->data == 'b');

  Node_signed_char_destructor(node);
}

void test_unsigned_char() {
  struct Node_unsigned_char* node = Node_unsigned_char_constructor('x');
  assert(node->data == 'x');

  node->data = 'y';
  assert(node->data == 'y');

  Node_unsigned_char_destructor(node);
}

void test_unsigned_short() {
  struct Node_unsigned_short* node = Node_unsigned_short_constructor(1234);
  assert(node->data == 1234);

  node->data = 5678;
  assert(node->data == 5678);

  Node_unsigned_short_destructor(node);
}

void test_unsigned_int() {
  struct Node_unsigned_int* node = Node_unsigned_int_constructor(12345);
  assert(node->data == 12345);

  node->data = 67890;
  assert(node->data == 67890);

  Node_unsigned_int_destructor(node);
}

void test_unsigned_long() {
  struct Node_unsigned_long* node = Node_unsigned_long_constructor(1234567890);
  assert(node->data == 1234567890);

  node->data = 9876543210;
  assert(node->data == 9876543210);

  Node_unsigned_long_destructor(node);
}

void test_long_long() {
  struct Node_long_long* node = Node_long_long_constructor(123456789012);
  assert(node->data == 123456789012);

  node->data = 987654321098;
  assert(node->data == 987654321098);

  Node_long_long_destructor(node);
}

void test_unsigned_long_long() {
  struct Node_unsigned_long_long* node = Node_unsigned_long_long_constructor(12345678901234);
  assert(node->data == 12345678901234);

  node->data = 98765432109876;
  assert(node->data == 98765432109876);

  Node_unsigned_long_long_destructor(node);
}

void test_char() {
  struct Node_char* node = Node_char_constructor('A');
  assert(node->data == 'A');

  node->data = 'B';
  assert(node->data == 'B');

  Node_char_destructor(node);
}

void test_short() {
  struct Node_short* node = Node_short_constructor(123);
  assert(node->data == 123);

  node->data = 456;
  assert(node->data == 456);

  Node_short_destructor(node);
}

void test_int() {
  struct Node_int* node = Node_int_constructor(12345);
  assert(node->data == 12345);

  node->data = 67890;
  assert(node->data == 67890);

  Node_int_destructor(node);
}

void test_long() {
  struct Node_long* node = Node_long_constructor(1234567890);
  assert(node->data == 1234567890);

  node->data = 9876543210;
  assert(node->data == 9876543210);

  Node_long_destructor(node);
}

void test_int8_t() {
  struct Node_int8_t* node = Node_int8_t_constructor(12);
  assert(node->data == 12);

  node->data = 34;
  assert(node->data == 34);

  Node_int8_t_destructor(node);
}

void test_uint8_t() {
  struct Node_uint8_t* node = Node_uint8_t_constructor(56);
  assert(node->data == 56);

  node->data = 78;
  assert(node->data == 78);

  Node_uint8_t_destructor(node);
}

void test_int16_t() {
  struct Node_int16_t* node = Node_int16_t_constructor(1234);
  assert(node->data == 1234);

  node->data = 5678;
  assert(node->data == 5678);

  Node_int16_t_destructor(node);
}

void test_uint16_t() {
  struct Node_uint16_t* node = Node_uint16_t_constructor(12345);
  assert(node->data == 12345);

  node->data = (uint16_t)67890;
  assert(node->data == (uint16_t)67890);

  Node_uint16_t_destructor(node);
}

void test_int32_t() {
  struct Node_int32_t* node = Node_int32_t_constructor(123456);
  assert(node->data == 123456);

  node->data = 789012;
  assert(node->data == 789012);

  Node_int32_t_destructor(node);
}

void test_uint32_t() {
  struct Node_uint32_t* node = Node_uint32_t_constructor(1234567);
  assert(node->data == 1234567);

  node->data = 8901234;
  assert(node->data == 8901234);

  Node_uint32_t_destructor(node);
}

void test_int64_t() {
  struct Node_int64_t* node = Node_int64_t_constructor(12345678);
  assert(node->data == 12345678);

  node->data = 90123456;
  assert(node->data == 90123456);

  Node_int64_t_destructor(node);
}

void test_uint64_t() {
  struct Node_uint64_t* node = Node_uint64_t_constructor(123456789);
  assert(node->data == 123456789);

  node->data = 987654321;
  assert(node->data == 987654321);

  Node_uint64_t_destructor(node);
}

void test_int_least8_t() {
  struct Node_int_least8_t* node = Node_int_least8_t_constructor(12);
  assert(node->data == 12);

  node->data = 34;
  assert(node->data == 34);

  Node_int_least8_t_destructor(node);
}

void test_uint_least8_t() {
  struct Node_uint_least8_t* node = Node_uint_least8_t_constructor(56);
  assert(node->data == 56);

  node->data = 78;
  assert(node->data == 78);

  Node_uint_least8_t_destructor(node);
}

void test_int_least16_t() {
  struct Node_int_least16_t* node = Node_int_least16_t_constructor(1234);
  assert(node->data == 1234);

  node->data = 5678;
  assert(node->data == 5678);

  Node_int_least16_t_destructor(node);
}

void test_uint_least16_t() {
  struct Node_uint_least16_t* node = Node_uint_least16_t_constructor(12345);
  assert(node->data == 12345);

  node->data = (uint_least16_t)67890;
  assert(node->data == (uint_least16_t)67890);

  Node_uint_least16_t_destructor(node);
}

void test_int_least32_t() {
  struct Node_int_least32_t* node = Node_int_least32_t_constructor(123456);
  assert(node->data == 123456);

  node->data = 789012;
  assert(node->data == 789012);

  Node_int_least32_t_destructor(node);
}

void test_uint_least32_t() {
  struct Node_uint_least32_t* node = Node_uint_least32_t_constructor(1234567);
  assert(node->data == 1234567);

  node->data = 8901234;
  assert(node->data == 8901234);

  Node_uint_least32_t_destructor(node);
}

void test_int_least64_t() {
  struct Node_int_least64_t* node = Node_int_least64_t_constructor(12345678);
  assert(node->data == 12345678);

  node->data = 90123456;
  assert(node->data == 90123456);

  Node_int_least64_t_destructor(node);
}

void test_uint_least64_t() {
  struct Node_uint_least64_t* node = Node_uint_least64_t_constructor(123456789);
  assert(node->data == 123456789);

  node->data = 987654321;
  assert(node->data == 987654321);

  Node_uint_least64_t_destructor(node);
}

void test_int_fast8_t() {
  struct Node_int_fast8_t* node = Node_int_fast8_t_constructor(12);
  assert(node->data == 12);

  node->data = 34;
  assert(node->data == 34);

  Node_int_fast8_t_destructor(node);
}

void test_uint_fast8_t() {
  struct Node_uint_fast8_t* node = Node_uint_fast8_t_constructor(56);
  assert(node->data == 56);

  node->data = 78;
  assert(node->data == 78);

  Node_uint_fast8_t_destructor(node);
}

void test_int_fast16_t() {
  struct Node_int_fast16_t* node = Node_int_fast16_t_constructor(1234);
  assert(node->data == 1234);

  node->data = 5678;
  assert(node->data == 5678);

  Node_int_fast16_t_destructor(node);
}

void test_uint_fast16_t() {
  struct Node_uint_fast16_t* node = Node_uint_fast16_t_constructor(12345);
  assert(node->data == 12345);

  node->data = 67890;
  assert(node->data == 67890);

  Node_uint_fast16_t_destructor(node);
}

void test_int_fast32_t() {
  struct Node_int_fast32_t* node = Node_int_fast32_t_constructor(123456);
  assert(node->data == 123456);

  node->data = 789012;
  assert(node->data == 789012);

  Node_int_fast32_t_destructor(node);
}

void test_uint_fast32_t() {
  struct Node_uint_fast32_t* node = Node_uint_fast32_t_constructor(1234567);
  assert(node->data == 1234567);

  node->data = 8901234;
  assert(node->data == 8901234);

  Node_uint_fast32_t_destructor(node);
}

void test_int_fast64_t() {
  struct Node_int_fast64_t* node = Node_int_fast64_t_constructor(12345678);
  assert(node->data == 12345678);

  node->data = 90123456;
  assert(node->data == 90123456);

  Node_int_fast64_t_destructor(node);
}

void test_uint_fast64_t() {
  struct Node_uint_fast64_t* node = Node_uint_fast64_t_constructor(123456789);
  assert(node->data == 123456789);

  node->data = 987654321;
  assert(node->data == 987654321);

  Node_uint_fast64_t_destructor(node);
}

void test_intptr_t() {
  struct Node_intptr_t* node = Node_intptr_t_constructor(123);
  assert(node->data == 123);

  node->data = 456;
  assert(node->data == 456);

  Node_intptr_t_destructor(node);
}

void test_uintptr_t() {
  struct Node_uintptr_t* node = Node_uintptr_t_constructor(789);
  assert(node->data == 789);

  node->data = 012;
  assert(node->data == 012);

  Node_uintptr_t_destructor(node);
}

void test_intmax_t() {
  struct Node_intmax_t* node = Node_intmax_t_constructor(12345);
  assert(node->data == 12345);

  node->data = 67890;
  assert(node->data == 67890);

  Node_intmax_t_destructor(node);
}

void test_uintmax_t() {
  struct Node_uintmax_t* node = Node_uintmax_t_constructor(54321);
  assert(node->data == 54321);

  node->data = 98760;
  assert(node->data == 98760);

  Node_uintmax_t_destructor(node);
}

void test_float() {
  struct Node_float* node = Node_float_constructor(1.23f);
  assert(node->data == 1.23f);

  node->data = 4.56f;
  assert(node->data == 4.56f);

  Node_float_destructor(node);
}

void test_double() {
  struct Node_double* node = Node_double_constructor(7.89);
  assert(node->data == 7.89);

  node->data = 0.12;
  assert(node->data == 0.12);

  Node_double_destructor(node);
}

void test_Bool() {
  struct Node__Bool* node = Node__Bool_constructor(1);
  assert(node->data == 1);

  node->data = 0;
  assert(node->data == 0);

  Node__Bool_destructor(node);
}

int main() {
  test_long_double();
  test_signed_char();
  test_unsigned_char();
  test_unsigned_short();
  test_unsigned_int();
  test_unsigned_long();
  test_long_long();
  test_unsigned_long_long();
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
  test_int_least8_t();
  test_uint_least8_t();
  test_int_least16_t();
  test_uint_least16_t();
  test_int_least32_t();
  test_uint_least32_t();
  test_int_least64_t();
  test_uint_least64_t();
  test_int_fast8_t();
  test_uint_fast8_t();
  test_int_fast16_t();
  test_uint_fast16_t();
  test_int_fast32_t();
  test_uint_fast32_t();
  test_int_fast64_t();
  test_uint_fast64_t();
  test_intptr_t();
  test_uintptr_t();
  test_intmax_t();
  test_uintmax_t();
  test_float();
  test_double();
  test_Bool();
  printf("node_macro.t ............... OK\n");
  return 0;
}

