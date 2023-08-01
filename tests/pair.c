#include "../include/pair.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test the creation and destruction of a node.
void test_creation_and_destruction() {
  char key[] = "dummy";
  int value = 10000000;
  struct Pair* pair = pair_constructor(&key,
      strlen(key) + 1, &value, sizeof(int));
  assert(strcmp((char*)pair->key, key) == 0);
  assert(*(int*)pair->value == value);
  pair_destructor(pair);
}

void test_integer_to_integer() {
  int key = 1, value = 100;
  struct Pair* pair = pair_constructor(&key,
      sizeof(int), &value, sizeof(int));

  // Access the key and value
  assert(*(int*)pair->key == key);
  assert(*(int*)pair->value == value);
}

void test_integer_to_character() {
  int key = 2;
  char* value = "example";
  struct Pair* pair = pair_constructor(&key,
      sizeof(int), value, strlen(value) + 1);

  // Access the key and value
  assert(*(int*)pair->key == key);
  assert(strcmp((char*)pair->value, value) == 0);
}

void test_character_to_character() {
  char* key = "some_key";
  char* value = "example";
  struct Pair* pair = pair_constructor(key,
      strlen(key) + 1, value, strlen(value) + 1);

  // Access the key and value
  assert(strcmp((char*)pair->key, key) == 0);
  assert(strcmp((char*)pair->value, value) == 0);
}

void test_character_to_integer() {
  char* key = "key";
  int value = 400;
  struct Pair* pair = pair_constructor(key,
      strlen(key) + 1, &value, sizeof(int));

  // Access the key and value
  assert(strcmp((char*)pair->key, key) == 0);
  assert(*(int*)pair->value == value);
}

// Test the integer (int) data type.
void test_primitive_int_array() {
  int key = 1;

  // test the array of integer (int[]) data type
  int nums[] = {1, 2, 3, 4, 5};
  size_t size_int = sizeof(nums) / sizeof(nums[0]);

  struct Pair* pair = pair_constructor(&key, sizeof(int),
      &nums, sizeof(int) * size_int);

  int *ptr_array = (int*)pair->value;
  for (size_t i = 0; i < size_int; i++) {
    // verify with a pointer
    assert(ptr_array[i] == nums[i]);

    // verify by direct access memory
    assert(((int*)pair->value)[i] == nums[i]);
  }

  pair_destructor(pair);
}

// Test the character (char) data type.
void test_primitive_char_array() {
  char* key = "key";

  // test the array of character (char[]) data type
  char letters[] = {'H', 'e', 'l', 'l', 'o'};
  size_t size_char = sizeof(letters) / sizeof(letters[0]);

  struct Pair* pair = pair_constructor(key, strlen(key),
      &letters, sizeof(char) * size_char);

  char *ptr_array = (char*)pair->value;
  for (size_t i = 0; i < size_char; i++) {
    // verify with a pointer
    assert(ptr_array[i] == letters[i]);

    // verify by direct access memory
    assert(((char*)pair->value)[i] == letters[i]);
  }

  pair_destructor(pair);
}

// Test the maximum limit of integer (unsigned long long) data type.
void test_primitive_long() {
  // make a global key to be used for each test of this function
  int key = 10;

  // test the maximum limit of integer (unsigned long long) data type
  unsigned long long data_max = 184467440737095516;

  struct Pair* pair_max = pair_constructor(&key, sizeof(key),
      &data_max, sizeof(data_max));

  // verify with a pointer
  unsigned long long *ptr_max = (unsigned long long*)pair_max->value;
  assert(*ptr_max == data_max);

  // verify by direct access memory
  assert(*(unsigned long long*)pair_max->value == 184467440737095516);

  pair_destructor(pair_max);
}

void test_custom_data() {
  // Declare the custom data type
  struct Test {
    int key;
    char* value;
  };

  int key = 0;
  struct Test test = { 100, "test" };

  // initialize and access pair data
  struct Pair* pair = pair_constructor(&key, sizeof(int),
      &test, sizeof(struct Test));

  // verify with a pointer
  struct Test *ptr_customized = (struct Test*)pair->value;
  assert(ptr_customized->key == test.key);
  assert(strcmp(ptr_customized->value, test.value) == 0);

  // verify by direct access memory
  assert(((struct Test*)pair->value)->key == 100);
  assert(strcmp(((struct Test*)pair->value)->value, "test") == 0);

  pair_destructor(pair);
}

int main() {
  test_creation_and_destruction();
  test_integer_to_integer();
  test_integer_to_character();
  test_character_to_character();
  test_character_to_integer();
  test_primitive_int_array();
  test_primitive_char_array();
  test_primitive_long();
  test_custom_data();
  printf("pair.t ..................... OK\n");
  return 0;
}
