#include "../include/set.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

COMPARE_SET(int, set_compare_int)
COMPARE_SET(char, set_compare_str)

// Test the creation and destruction of a set.
void test_creation_and_destruction() {
  struct Set* set = new_set(set_compare_int);
  destroy_set(set);
}

// Test the "insert_dict" and the "search_dict" functions.
void test_insert_and_search() {
  // create a new instance of a Set
  struct Set* set = new_set(set_compare_int);

  // insert ten new entries
  for (int i = 0; i < 10; ++i) {
    int val = i * 100;

    // use the "i" variable as the "key" and the "val" variable as the value
    set->insert(set, &i, sizeof(int), &val, sizeof(int));
  }


  // search for the newlly created entries
  for (int i = 0; i < 10; ++i) {
    int searchable = *(int*)set->search(set, &i, sizeof(int));

    // check the data inserted
    assert(searchable == i * 100);
  }

  // search again, but in reverse
  for (int i = 9; i >= 0; --i) {
     int searchable = *(int*)set->search(set, &i, sizeof(int));

     // check the data inserted
     assert(searchable == i * 100);
  }

  destroy_set(set);
}

// Test case for remove() method
void test_remove() {
  struct Set* set = new_set(set_compare_int);

  // insert 10 new entries
  for (int i = 0; i < 10; ++i) {
    set->insert(set, &i, sizeof(int), &i, sizeof(int));
  }

  // remove the pair and check it's existance
  int pair_to_remove = 5;
  set->remove(set, &pair_to_remove, sizeof(int));
  assert(set->search(set, &pair_to_remove, sizeof(int)) == NULL);

  pair_to_remove = 0;
  set->remove(set, &pair_to_remove, sizeof(int));
  assert(set->search(set, &pair_to_remove, sizeof(int)) == NULL);

  pair_to_remove = 9;
  set->remove(set, &pair_to_remove, sizeof(int));
  assert(set->search(set, &pair_to_remove, sizeof(int)) == NULL);

  destroy_set(set);
}

// Test comparing strings in the binary tree
void test_string_comparison() {
  struct Set* set = new_set(set_compare_str);

  char key1[] = "1";
  char val1[] = "apple";
  set->insert(set, &key1, strlen(key1) + 1, &val1, strlen(val1) + 1);

  char key2[] = "2";
  char val2[] = "banana";
  set->insert(set, &key2, strlen(key2) + 1, &val2, strlen(val2) + 1);

  char key3[] = "3";
  char val3[] = "cherry";
  set->insert(set, &key3, strlen(key3) + 1, &val3, strlen(val3) + 1);

  char* found1 = (char*)set->search(set, &key1, strlen(key1) + 1);
  char* found2 = (char*)set->search(set, &key2, strlen(key2) + 1);
  char* found3 = (char*)set->search(set, &key3, strlen(key3) + 1);

  assert(strcmp(found1, val1) == 0);
  assert(strcmp(found2, val2) == 0);
  assert(strcmp(found3, val3) == 0);

  destroy_set(set);
}

int main() {
  test_creation_and_destruction();
  test_insert_and_search();
  test_remove();
  test_string_comparison();
  printf("set.t ...................... OK\n");
  return 0;
}