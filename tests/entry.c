#include "../include/entry.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_integer_to_integer() {
  int key = 1, value = 100;
  struct Entry* entry = entry_constructor(&key, sizeof(int),
      &value, sizeof(int));

  // Access the key and value
  assert(*(int*)entry->key == key);
  assert(*(int*)entry->value == value);
}

void test_integer_to_character() {
  int key = 2;
  char* value = "example";
  struct Entry* entry = entry_constructor(&key, sizeof(int),
      value, strlen(value) * sizeof(char));

  // Access the key and value
  assert(*(int*)entry->key == key);
  assert(strcmp((char*)entry->value, value) == 0);
}

void test_character_to_character() {
  char* key = "key";
  char* value = "example";
  struct Entry* entry = entry_constructor(key, strlen(key) * sizeof(char),
      value, strlen(value) * sizeof(char));

  // Access the key and value
  assert(strcmp((char*)entry->key, key) == 0);
  assert(strcmp((char*)entry->value, value) == 0);
}

void test_character_to_integer() {
  char* key = "key";
  int value = 400;
  struct Entry* entry = entry_constructor(key, strlen(key) * sizeof(char),
      &value, sizeof(int));

  // Access the key and value
  assert(strcmp((char*)entry->key, key) == 0);
  assert(*(int*)entry->value == value);
}

// Test the integer (int) data type.
void test_primitive_int_array() {
  int key = 1;

  // test the array of integer (int[]) data type
  int nums[] = {1, 2, 3, 4, 5};
  size_t size_int = sizeof(nums) / sizeof(nums[0]);

  struct Entry* entry = entry_constructor(&key, sizeof(int),
      &nums, sizeof(int) * size_int);

  int *ptr_array = (int*)entry->value;
  for (size_t i = 0; i < size_int; i++) {
    // verify with a pointer
    assert(ptr_array[i] == nums[i]);

    // verify by direct access memory
    assert(((int*)entry->value)[i] == nums[i]);
  }

  entry_destructor(entry);
}

// Test the character (char) data type.
void test_primitive_char_array() {
  char* key = "key";

  // test the array of character (char[]) data type
  char letters[] = {'H', 'e', 'l', 'l', 'o'};
  size_t size_char = sizeof(letters) / sizeof(letters[0]);

  struct Entry* entry = entry_constructor(key, strlen(key),
      &letters, sizeof(char) * size_char);

  char *ptr_array = (char*)entry->value;
  for (size_t i = 0; i < size_char; i++) {
    // verify with a pointer
    assert(ptr_array[i] == letters[i]);

    // verify by direct access memory
    assert(((char*)entry->value)[i] == letters[i]);
  }

  entry_destructor(entry);
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

void test_custom_data() {
  // Declare the custom data type
  struct Test {
    int key;
    char* value;
  };

  int key = 0;
  struct Test test = { 100, "test" };

  // initialize and access entry data
  struct Entry* entry = entry_constructor(&key, sizeof(int),
      &test, sizeof(struct Test));

  // verify with a pointer
  struct Test *ptr_customized = (struct Test*)entry->value;
  assert(ptr_customized->key == test.key);
  assert(strcmp(ptr_customized->value, test.value) == 0);

  // verify by direct access memory
  assert(((struct Test*)entry->value)->key == 100);
  assert(strcmp(((struct Test*)entry->value)->value, "test") == 0);

  entry_destructor(entry);
}

int main() {
  test_integer_to_integer();
  test_integer_to_character();
  test_character_to_character();
  test_character_to_integer();
  test_primitive_int_array();
  test_primitive_char_array();
  test_primitive_long();
  test_custom_data();
  printf("entry.t .................... OK\n");
  return 0;
}
