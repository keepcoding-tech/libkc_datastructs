#include "../include/entry.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the integer (int) data type.
void test_primitive_int() {
  // make a global key to be used for each test of this function
  int key = 10;

  // test the integer (int) data type
  int data_int = 10;

  struct Entry* entry_int = entry_constructor(&key, sizeof(key),
      &data_int, sizeof(data_int));

  // verify with a pointer
  int *ptr_int = (int*)entry_int->value;
  assert(*ptr_int == data_int);

  // verify by direct access memory
  assert(*(int*)entry_int->value == 10);

  entry_destructor(entry_int);

  // test the array of integer (int[]) data type
  int data_int_array[] = {1, 2, 3, 4, 5};
  size_t size_int = sizeof(data_int_array) / sizeof(data_int_array[0]);

  struct Entry* entry_int_array = entry_constructor(&key, sizeof(key),
      &data_int_array, sizeof(int) * size_int);

  int *ptr_int_array = (int*)entry_int_array->value;
  for (size_t i = 0; i < size_int; i++) {
    // verify with a pointer
    assert(ptr_int_array[i] == data_int_array[i]);

    // verify by direct access memory
    assert(((int*)entry_int_array->value)[i] == data_int_array[i]);
  }

  entry_destructor(entry_int_array);
}

// Test the character (char) data type.
void test_primitive_char() {
  // make a global key to be used for each test of this function
  int key = 10;

  // test the character (char) data type
  char data_char = 'A';

  struct Entry* entry_char = entry_constructor(&key, sizeof(key),
      &data_char, sizeof(data_char));

  // verify with a pointer
  char *ptr_char = (char*)entry_char->value;
  assert(*ptr_char == data_char);

  // verify by direct access memory
  assert(*(char*)entry_char->value == 'A');

  entry_destructor(entry_char);

  // test the array of character (char[]) data type
  char data_char_array[] = {'H', 'e', 'l', 'l', 'o'};
  size_t size_char = sizeof(data_char_array) / sizeof(data_char_array[0]);

  struct Entry* entry_char_array = entry_constructor(&key, sizeof(key),
      &data_char_array, sizeof(int) * size_char);

  char *ptr_char_array = (char*)entry_char_array->value;
  for (size_t i = 0; i < size_char; i++) {
    // verify with a pointer
    assert(ptr_char_array[i] == data_char_array[i]);

    // verify by direct access memory
    assert(((char*)entry_char_array->value)[i] == data_char_array[i]);
  }

  entry_destructor(entry_char_array);
}

// Test the maximum limit of integer (unsigned long long) data type.
void test_primitive_long() {
  // make a global key to be used for each test of this function
  int key = 10;

  // test the maximum limit of integer (unsigned long long) data type
  unsigned long long data_max = 184467440737095516;

  struct Entry* entry_max = entry_constructor(&key, sizeof(key),
      &data_max, sizeof(data_max));

  // verify with a pointer
  unsigned long long *ptr_max = (unsigned long long*)entry_max->value;
  assert(*ptr_max == data_max);

  // verify by direct access memory
  assert(*(unsigned long long*)entry_max->value == 184467440737095516);

  entry_destructor(entry_max);
}

int main() {
  test_primitive_int();
  test_primitive_char();
  test_primitive_long();
  printf("entry.t .................... OK\n");
  return 0;
}
