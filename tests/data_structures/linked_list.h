/*
  This is a file for testing the LinkedList data structure public members. The
  private members are used by the public ones, so testing is not required.
*/

#ifndef linked_list_test_h
#define linked_list_test_h

#include <stdio.h>

#include "../../data_structures/lists/LinkedList.h"

// Run all the tests in the file.
void linked_list_tests();

// Test the "insert_node_ll" function.
void insert_node();

// Test the  "remove_node_ll" function.
void remove_node();

// Test the "retrieve_node_ll" function.
void retrieve_node();

#endif /* linked_list_test_h */
