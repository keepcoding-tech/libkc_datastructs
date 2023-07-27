#include "../include/set.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test the creation and destruction of a dictionary.
void test_creation_and_destruction() {
  struct Dictionary* dictionary = new_dictionary(dict_compare_int);
  assert(dictionary->keys->head == NULL);
  destroy_dictionary(dictionary);
}

// Test the "insert_dict" and the "search_dict" functions.
void test_insert_and_search() {
  // create a new instance of a Dictionary
  struct Dictionary* dictionary = new_dictionary(dict_compare_int);

  // insert ten new entries
  for (int i = 0; i < 10; ++i) {
    int val = i * 100;

    // use the "i" variable as the "key" and the "val" variable as the value
    dictionary->insert(dictionary, &i, sizeof(i), &val, sizeof(val));
  }


  // search for the newlly created entries
  for (int i = 0; i < 10; ++i) {
    int searchable = *(int*)dictionary->search(dictionary, &i, sizeof(i));

    // check the data inserted
    assert(searchable == i * 100);
  }

  // search again, but in reverse
  for (int i = 9; i >= 0; --i) {
     int searchable = *(int*)dictionary->search(dictionary, &i, sizeof(i));

     // check the data inserted
     assert(searchable == i * 100);
  }

  destroy_dictionary(dictionary);
}

// Test comparing strings in the binary tree
void test_string_comparison() {
  struct Dictionary* dictionary = new_dictionary(dict_compare_str);

  char* key1 = "1";
  char* val1 = "apple";
  dictionary->insert(dictionary, &key1, sizeof(key1), val1, strlen(val1) + 1);

  char* key2 = "2";
  char* val2 = "banana";
  dictionary->insert(dictionary, &key2, sizeof(key2), val2, strlen(val2) + 1);

  char* key3 = "3";
  char* val3 = "cherry";
  dictionary->insert(dictionary, &key3, sizeof(key3), val3, strlen(val3) + 1);

  char* found1 = (char*)dictionary->search(dictionary, &key1, sizeof(key1));
  char* found2 = (char*)dictionary->search(dictionary, &key2, sizeof(key2));
  char* found3 = (char*)dictionary->search(dictionary, &key3, sizeof(key3));

  assert(strcmp(found1, val1) == 0);
  assert(strcmp(found2, val2) == 0);
  assert(strcmp(found3, val3) == 0);

  destroy_dictionary(dictionary);
}

int main() {
  test_creation_and_destruction();
  test_insert_and_search();
  //test_string_comparison();
  printf("dictionary.t ............... OK\n");
  return 0;
}
