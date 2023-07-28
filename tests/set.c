#include "../include/set.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
// Test the creation and destruction of a set.
void test_creation_and_destruction() {
  struct Set* set = new_set(dict_compare_int);
=======
COMPARE_SET(int, set_compare_int)
COMPARE_SET(char, set_compare_str)

// Test the creation and destruction of a set.
void test_creation_and_destruction() {
  struct Set* set = new_set(set_compare_int);
>>>>>>> refactor: set naming conv
  destroy_set(set);
}

// Test the "insert_dict" and the "search_dict" functions.
void test_insert_and_search() {
  // create a new instance of a Set
<<<<<<< HEAD
  struct Set* set = new_set(dict_compare_int);
=======
  struct Set* set = new_set(set_compare_int);
>>>>>>> refactor: set naming conv

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

// Test comparing strings in the binary tree
void test_string_comparison() {
<<<<<<< HEAD
  struct Set* set = new_set(dict_compare_str);
=======
  struct Set* set = new_set(set_compare_str);
>>>>>>> refactor: set naming conv

  char key1[] = "1";
  char val1[] = "apple";
  set->insert(set, &key1, strlen(key1) * sizeof(char),
      &val1, strlen(val1) * sizeof(char));

  char key2[] = "2";
  char val2[] = "banana";
  set->insert(set, &key2, strlen(key2) * sizeof(char),
      &val2, strlen(val2) * sizeof(char));

  char key3[] = "3";
  char val3[] = "cherry";
  set->insert(set, &key3, strlen(key3) * sizeof(char),
      &val3, strlen(val3) * sizeof(char));

  char* found1 = (char*)set->search(set, &key1, strlen(key1) * sizeof(char));
  char* found2 = (char*)set->search(set, &key2, strlen(key2) * sizeof(char));
  char* found3 = (char*)set->search(set, &key3, strlen(key3) * sizeof(char));

  assert(strcmp(found1, val1) == 0);
  assert(strcmp(found2, val2) == 0);
  assert(strcmp(found3, val3) == 0);

  destroy_set(set);
}

int main() {
  test_creation_and_destruction();
  test_insert_and_search();
  test_string_comparison();
  printf("set.t ...................... OK\n");
  return 0;
}
