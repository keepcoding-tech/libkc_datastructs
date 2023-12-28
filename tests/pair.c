// This file is part of libkc_datastructs
// ==================================
//
// pair.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../deps/libkc/testing/testing.h"
#include "../include/pair.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  testgroup("Pair")
  {
    subtest("test creation and destruction")
    {
      char key[] = "dummy";
      int value = 10000000;
      struct Pair* pair = pair_constructor(&key,
        strlen(key) + 1, &value, sizeof(int));
      ok(strcmp((char*)pair->key, key) == 0);
      ok(*(int*)pair->value == value);
      pair_destructor(pair);
    }

    subtest("test integer to integer")
    {
      int key = 1, value = 100;
      struct Pair* pair = pair_constructor(&key,
        sizeof(int), &value, sizeof(int));

      // Access the key and value
      ok(*(int*)pair->key == key);
      ok(*(int*)pair->value == value);
    }

    subtest("test integer to character")
    {
      int key = 2;
      char* value = "example";
      struct Pair* pair = pair_constructor(&key,
        sizeof(int), value, strlen(value) + 1);

      // Access the key and value
      ok(*(int*)pair->key == key);
      ok(strcmp((char*)pair->value, value) == 0);
    }

    subtest("test character to character")
    {
      char* key = "some_key";
      char* value = "example";
      struct Pair* pair = pair_constructor(key,
        strlen(key) + 1, value, strlen(value) + 1);

      // Access the key and value
      ok(strcmp((char*)pair->key, key) == 0);
      ok(strcmp((char*)pair->value, value) == 0);
    }

    subtest("test character to integer") {
      char* key = "key";
      int value = 400;
      struct Pair* pair = pair_constructor(key,
        strlen(key) + 1, &value, sizeof(int));

      // Access the key and value
      ok(strcmp((char*)pair->key, key) == 0);
      ok(*(int*)pair->value == value);
    }

    subtest("test primitive int array")
    {
      int key = 1;

      // test the array of integer (int[]) data type
      int nums[] = { 1, 2, 3, 4, 5 };
      size_t size_int = sizeof(nums) / sizeof(nums[0]);

      struct Pair* pair = pair_constructor(&key, sizeof(int),
        &nums, sizeof(int) * size_int);

      int* ptr_array = (int*)pair->value;
      for (size_t i = 0; i < size_int; i++)
      {
        // verify with a pointer
        ok(ptr_array[i] == nums[i]);

        // verify by direct access memory
        ok(((int*)pair->value)[i] == nums[i]);
      }

      pair_destructor(pair);
    }

    subtest("test primitive char array")
    {
      char* key = "key";

      // test the array of character (char[]) data type
      char letters[] = { 'H', 'e', 'l', 'l', 'o' };
      size_t size_char = sizeof(letters) / sizeof(letters[0]);

      struct Pair* pair = pair_constructor(key, strlen(key),
        &letters, sizeof(char) * size_char);

      char* ptr_array = (char*)pair->value;
      for (size_t i = 0; i < size_char; i++)
      {
        // verify with a pointer
        ok(ptr_array[i] == letters[i]);

        // verify by direct access memory
        ok(((char*)pair->value)[i] == letters[i]);
      }

      pair_destructor(pair);
    }

    subtest("test primitive long")
    {
      // make a global key to be used for each test of this function
      int key = 10;

      // test the maximum limit of integer (unsigned long long) data type
      unsigned long long data_max = 184467440737095516;

      struct Pair* pair_max = pair_constructor(&key, sizeof(key),
        &data_max, sizeof(data_max));

      // verify with a pointer
      unsigned long long* ptr_max = (unsigned long long*)pair_max->value;
      ok(*ptr_max == data_max);

      // verify by direct access memory
      ok(*(unsigned long long*)pair_max->value == 184467440737095516);

      pair_destructor(pair_max);
    }

    subtest("test custom data")
    {
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
      struct Test* ptr_customized = (struct Test*)pair->value;
      ok(ptr_customized->key == test.key);
      ok(strcmp(ptr_customized->value, test.value) == 0);

      // verify by direct access memory
      ok(((struct Test*)pair->value)->key == 100);
      ok(strcmp(((struct Test*)pair->value)->value, "test") == 0);

      pair_destructor(pair);
    }

    done_testing()
  }

  return 0;
}
