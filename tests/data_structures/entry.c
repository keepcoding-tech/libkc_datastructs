#include "entry.h"

void entry_tests();
void members_fields();

void entry_tests() {
  members_fields();
  printf("entry.t .................... OK\n");
}

// Test the members of the Entry structure.
void members_fields() {
  char *key = "test";
  int value = 200;

  struct Entry entry =
    entry_constructor(key, sizeof(key), &value, sizeof(value));

  // check if the "key" was stored correctly
  assert(*(char *)entry.key == *(char *)"test");

  // check if the "value" was stored correctly
  assert(*(int *)entry.value == 200);

  // destroy the entry
  entry_destructor(&entry);
}
