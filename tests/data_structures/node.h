/*
 This is a file for testing the Node data structure public members. The private
 members are used by the public ones, so testing is not required.
*/

#ifndef node_test_h
#define node_test_h

#include <stdio.h>
#include <stdlib.h>

#include "../../data_structures/utils/Node.h"

// Run all the tests in the file.
void node_tests();

// Test the integer data type.
void int_data_type();

// Test the character data type.
void char_data_type();

// Test a new structure.
void struct_data_type();

#endif /* node_test_h */
