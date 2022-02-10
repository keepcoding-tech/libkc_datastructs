#include "dictionary.h"

void dictionary_tests();

void insert_and_search_dict();

void dictionary_tests() {
  insert_and_search_dict();
  printf("dictionary.t ............... OK\n");
}

// Display where the test failed.
void failed_dict(char *test, int line) {
  printf("FAIELD -> %s at line %d\n", test, line);
  exit(1);
}

// Test the "insert_dict" and the "search_dict" functions.
void insert_and_search_dict() {
  // create a new instance of a Dictionary
  struct Dictionary dictionary = dictionary_constructor(compare_int_keys);

  // insert ten new entries
  for (int i = 0; i < 10; ++i) {
    int val = i * 100;
    // use the "i" variable as the "key" and the "val" variable as the value
    dictionary.insert(&dictionary, &i, sizeof(i), &val, sizeof(val));
  }

  for (int i = 9; i > 0; --i) {
    // check if the entries of the dictionary have been
    // inserted and retrieved corectly
    int searchable = *(int *)dictionary.search(&dictionary, &i, sizeof(i));
    if (searchable != i * 100) {
      failed_dict("insert_and_search_dict", 33);
    }
  }

  dictionary_destructor(&dictionary);
}
