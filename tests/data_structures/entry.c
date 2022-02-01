#include "entry.h"

void entry_tests();

void members_fields();

void entry_tests() {
  members_fields();
  printf("entry.t .................... OK\n");
}

// Display where the test failed.
void failed_et(char *test, int line) {
  printf("FAIELD -> %s at line %d\n", test, line);
  exit(1);
}

// Test the members of the Entry structure.
void members_fields() {
  char *key = "test";
  int value = 200;

  struct Entry entry =
    entry_constructor(key, sizeof(key), &value, sizeof(value));

  // check if the "key" was stored correctly
  if (*(char *)entry.key != *(char *)"test") {
    failed_et("constructor_and_destructor", 27);
  }

  // check if the "value" was stored correctly
  if (*(int *)entry.value != 200) {
    failed_et("constructor_and_destructor", 31);
  }

  // destroy the entry
  entry_destructor(&entry);
}
