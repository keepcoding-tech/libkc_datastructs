// This file is part of keepcoding_core
// ==================================
//
// datastructs.c
//
// Copyright (c) 2024 Daniel Tanase
// SPDX-License-Identifier: MIT License

#include "../hdrs/datastructs/list.h"
#include "../hdrs/datastructs/node.h"
#include "../hdrs/datastructs/pair.h"
#include "../hdrs/datastructs/queue.h"
#include "../hdrs/datastructs/set.h"
#include "../hdrs/datastructs/tree.h"
#include "../hdrs/datastructs/stack.h"
#include "../hdrs/datastructs/vector.h"

#include "../hdrs/test.h"
#include "../hdrs/common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Test case for the search() and remove() method of kc_list_t.
int test_list_compare(const void* data_one, const void* data_two)
{
  return (*(int*)data_one - *(int*)data_two);
}

COMPARE_LIST(int, compare_int)
COMPARE_LIST(char, compare_char)
COMPARE_LIST(int8_t, compare_int8_t)

COMPARE_SET(int, set_compare_int)
COMPARE_SET(char, set_compare_str)

COMPARE_TREE(int, btree_compare_int)
COMPARE_TREE(char, btree_compare_str)

// Test case for kc_tree_t.
int test_tree_compare(const void* a, const void* b)
{
  return (*(int*)(((struct kc_pair_t*)a)->key) -
    *(int*)(((struct kc_pair_t*)b)->key));
}

// Test case for the search() and remove() method of kc_vector_t.
int test_vector_compare(const void* a, const void* b)
{
  return (*(int*)a - *(int*)b);
}

int main() {
  testgroup("kc_list_t")
  {
    subtest("test init/desc")
    {
      struct kc_list_t* list = new_list();

      ok(list->_head == NULL);
      ok(list->_tail == NULL);

      destroy_list(list);
    }

    subtest("test back()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      struct kc_node_t* back = NULL;
      int ret = KC_INVALID;

      ret = list->back(list, &back);

      // there shouldn't be any nodes
      ok(ret == KC_SUCCESS);
      ok(back == NULL);

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check if the last element is returned correctly
        ret = list->back(list, &back);

        ok(ret == KC_SUCCESS);
        ok(*(int*)back->data == i);
      }

      // remove all the nodes
      for (int i = 9; i >= 0; --i)
      {
        // check if the last element is returned correctly
        ret = list->back(list, &back);

        ok(ret == KC_SUCCESS);
        ok(*(int*)back->data == i);

        ret = list->erase(list, i);

        ok(ret == KC_SUCCESS);
      }

      destroy_list(list);
    }

    subtest("test clear()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      bool is_empty = false;
      int ret = KC_INVALID;

      ret = list->empty(list, &is_empty);

      // the list should be empty
      ok(ret == KC_SUCCESS);
      ok(is_empty == true);

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // the list should not be empty now
      ret = list->empty(list, &is_empty);

      ok(ret == KC_SUCCESS);
      ok(list->length == 10);
      ok(is_empty == false);

      // clear the list
      list->clear(list);

      // the list should be empty again
      ret = list->empty(list, &is_empty);

      ok(ret == KC_SUCCESS);
      ok(is_empty == true);

      destroy_list(list);
    }

    subtest("test empty()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      bool is_empty = false;
      int ret = KC_INVALID;

      ret = list->empty(list, &is_empty);

      // the list should be empty
      ok(ret == KC_SUCCESS);
      ok(is_empty == true);

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // the list should not be empty now
      ret = list->empty(list, &is_empty);

      ok(ret == KC_SUCCESS);
      ok(is_empty == false);

      // remove all nodes
      for (int i = 0; i < 10; ++i)
      {
        list->erase(list, 0);
      }

      // the list should be empty again
      ret = list->empty(list, &is_empty);

      ok(ret == KC_SUCCESS);
      ok(is_empty == true);

      destroy_list(list);
    }

    subtest("test erase()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // remove the node from position 5
      ret = list->erase(list, 5);

      ok(ret == KC_SUCCESS);

      // check if the node was correctly removed
      struct kc_node_t* cursor = list->_head;
      for (int i = 0; i < 5; ++i)
      {
        cursor = cursor->next;
      }

      ok(*(int*)cursor->data != 4 || list->length != 10);

      // remove the head of the list
      ret = list->erase(list, 0);

      ok(ret == KC_SUCCESS);

      // check if the head of the list was correctly removed
      cursor = list->_head;
      ok(*(int*)cursor->data != 0 || list->length != 9);

      // remove the remaining nodes in reverse
      for (int i = (int)list->length - 1; i >= 0; --i)
      {
        ret = list->erase(list, i);

        ok(ret == KC_SUCCESS);
        ok(list->length == i);
      }

      destroy_list(list);
    }

    subtest("test front()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      struct kc_node_t* front = NULL;
      int ret = KC_INVALID;

      // there shouldn't be any nodes
      ret = list->front(list, &front);

      ok(ret == KC_SUCCESS);
      ok(front == NULL);

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check if the first element is returned correctly,
        // it should always be zero (the same value)
        ret = list->front(list, &front);

        ok(ret == KC_SUCCESS);
        ok(*(int*)front->data == 0);
      }

      // remove all the nodes
      for (int i = 0; i < 10; ++i)
      {
        // check if the first element is returned correctly
        ret = list->front(list, &front);

        ok(ret == KC_SUCCESS);
        ok(*(int*)front->data == i);

        // erase only the first node for each iteration
        ret = list->erase(list, 0);
        ok(ret == KC_SUCCESS);
      }

      destroy_list(list);
    }

    subtest("test get()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      struct kc_node_t* node = NULL;
      int ret = KC_INVALID;

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // check if the node was correctly retrieved
      ret = list->get(list, 5, &node);

      ok(ret == KC_SUCCESS);
      ok(*(int*)node->data == 5);

      // check if the head of the list was correctly retrieved
      ret = list->get(list, 0, &node);

      ok(ret == KC_SUCCESS);
      ok(*(int*)node->data == 0);

      // check if the tail of the list was correctly retrieved
      ret = list->get(list, (int)list->length - 1, &node);

      ok(ret == KC_SUCCESS);
      ok(*(int*)node->data == 9);

      destroy_list(list);
    }

    subtest("test insert()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;

      // add ten new nodes of type int
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        // check the length of the list
        ok(ret == KC_SUCCESS);
        ok(list->length == i + 1);
      }

      // add ten new nodes of type char
      for (int i = 10; i < 20; ++i)
      {
        char c = 'a' + i;
        ret = list->insert(list, i, &c, sizeof(char));

        // check the length of the list
        ok(ret == KC_SUCCESS);
        ok(list->length == i + 1);
      }

      for (int i = 0; i < 20; ++i)
      {
        struct kc_node_t* cursor = list->_head;
        for (int j = 0; j < i; ++j)
        {
          cursor = cursor->next;
        }

        // check if the nodes have been inserted correctly
        if (i < 10)
        {
          ok(*(int*)cursor->data == i);
        }
        else
        {
          ok(*(char*)cursor->data == 'a' + i);
        }
      }

      // add a new node of type int[] (array)
      int nums[] = {1, 2, 3, 4, 5};
      size_t size = sizeof(nums) / sizeof(nums[0]);
      ret = list->insert(list, 20, &nums, sizeof(int) * size);

      ok(ret == KC_SUCCESS);

      // get the 21st node
      struct kc_node_t* cursor = list->_tail;

      // check if the node has been inserted correctly
      int* ptr = (int*)cursor->data;
      for (int i = 0; i < size; ++i)
      {
        ok(ptr[i] == nums[i]);
      }

      destroy_list(list);
    }

    subtest("test pop_back()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        // the length should be reduced only after the pop
        ok(*(int*)list->_tail->data == 10 - (i + 1));
        ok(list->length == 10 - i);

        // check if the last node was deleted correctly
        ret = list->pop_back(list);

        ok(ret == KC_SUCCESS);
        ok(list->length == 10 - (i + 1));
      }

      destroy_list(list);
    }

    subtest("test pop_front()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        // the length should be reduced only after the pop
        ok(*(int*)list->_head->data == i);
        ok(list->length == 10 - i);

        ret = list->pop_front(list);

        // check if the last node was deleted correctly
        ok(ret == KC_SUCCESS);
        ok(list->length == 10 - (i + 1));
      }

      destroy_list(list);
    }

    subtest("test push_back()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;

      // push back ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        // the length should be incremented only after push
        ok(list->length == i);

        ret = list->push_back(list, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check if the node was inserted correctly
        ok(*(int*)list->_tail->data == i);
        ok(list->length == i + 1);
      }

      destroy_list(list);
    }

    subtest("test push_front()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;

      // push back ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        // the length should be incremented only after push
        ok(list->length == i);

        ret = list->push_front(list, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check if the node was inserted correctly
        ok(*(int*)list->_head->data == i);
        ok(list->length == i + 1);
      }

      destroy_list(list);
    }

    subtest("test remove()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;
      bool is_empty = false;

      // use the same data
      int data = 10;

      // add 5 new nodes
      for (int i = 0; i < 5; ++i)
      {
        ret = list->insert(list, i, &data, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      data = 20;

      // add 5 new nodes
      for (int i = 5; i < 10; ++i)
      {
        ret = list->insert(list, i, &data, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // should remove only 5 nodes
      ret = list->remove(list, &data, test_list_compare);

      ok(ret == KC_SUCCESS);
      ok(list->length == 5);

      data = 10;

      // should remove all 5 nodes
      ret = list->remove(list, &data, test_list_compare);
      ok(ret == KC_SUCCESS);

      ret = list->empty(list, &is_empty);
      ok(ret == KC_SUCCESS);

      ok(is_empty == true);

      destroy_list(list);
    }

    subtest("test search()")
    {
      // create a new instance of a List
      struct kc_list_t* list = new_list();

      int ret = KC_INVALID;

      // insert ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = list->insert(list, i, &i, sizeof(int));
      }

      // check if the values are in the list
      for (int i = 9; i > 0; --i)
      {
        bool exists = false;

        ret = list->search(list, &i, test_list_compare, &exists);

        ok(ret == KC_SUCCESS);
        ok(exists == true);
      }

      // check if the values are not in the list
      for (int i = 30; i > 20; --i)
      {
        bool exists = true;

        ret = list->search(list, &i, test_list_compare, &exists);

        ok(ret == KC_SUCCESS);
        ok(exists == false);
      }

      destroy_list(list);
    }

    subtest("test COMPARE_LIST")
    {
      int a_int = 1, b_int = 2;
      ok(compare_int(&a_int, &b_int) < 0);

      a_int = 2, b_int = 1;
      ok(compare_int(&a_int, &b_int) > 0);

      a_int = 1, b_int = 1;
      ok(compare_int(&a_int, &b_int) == 0);

      char a_char = 'a', b_char = 'b';
      ok(compare_char(&a_char, &b_char) < 0);

      a_char = 'b', b_char = 'a';
      ok(compare_char(&a_char, &b_char) > 0);

      a_char = 'a', b_char = 'a';
      ok(compare_char(&a_char, &b_char) == 0);

      int8_t a_int8_t = 1, b_int8_t = 2;
      ok(compare_int8_t(&a_int8_t, &b_int8_t) < 0);

      a_int8_t = 2, b_int8_t = 1;
      ok(compare_int8_t(&a_int8_t, &b_int8_t) > 0);

      a_int8_t = 1, b_int8_t = 1;
      ok(compare_int8_t(&a_int8_t, &b_int8_t) == 0);
    }

    done_testing()
  }

  testgroup("kc_node_t")
  {
    subtest("test init/desc")
    {
      int data = 10000;

      struct kc_node_t* node = node_constructor(&data, sizeof(int));

      ok(*(int*)node->data == data);
      ok(node->next == NULL);
      ok(node->prev == NULL);

      node_destructor(node);
    }

    subtest("test int")
    {
      // initialize the node
      int num = 10;
      struct kc_node_t* node_int = node_constructor(&num, sizeof(int));

      // verify with a pointer
      int* ptr_int = (int*)node_int->data;
      ok(*ptr_int == num);

      // verify by direct access memory
      ok(*(int*)node_int->data == 10);

      node_destructor(node_int);

      // test the array of integer (int[]) data type
      int nums[] = { 1, 2, 3, 4, 5 };
      size_t size_int = sizeof(nums) / sizeof(nums[0]);
      struct kc_node_t* node_array = node_constructor(nums, sizeof(int) * size_int);

      int* ptr_array = (int*)node_array->data;
      for (size_t i = 0; i < size_int; i++)
      {
        // verify with a pointer
        ok(ptr_array[i] == nums[i]);

        // verify by direct access memory
        ok(((int*)node_array->data)[i] == nums[i]);
      }

      node_destructor(node_array);
    }

    subtest("test char")
    {
      // initialize the node
      char letter = 'A';
      struct kc_node_t* node_char = node_constructor(&letter, sizeof(char));

      // verify with a pointer
      char* ptr_char = (char*)node_char->data;
      ok(*ptr_char == letter);

      // verify by direct access memory
      ok(*(char*)node_char->data == 'A');

      node_destructor(node_char);

      // test the array of character (char[]) data type
      char letters[] = { 'H', 'e', 'l', 'l', 'o' };
      size_t size_char = sizeof(letters) / sizeof(letters[0]);

      struct kc_node_t* node_array = node_constructor(letters, sizeof(char) * size_char);

      char* ptr_array = (char*)node_array->data;
      for (size_t i = 0; i < size_char; i++)
      {
        // verify with a pointer
        ok(ptr_array[i] == letters[i]);

        // verify by direct access memory
        ok(((char*)node_array->data)[i] == letters[i]);
      }

      // test the string (char*) data type
      char* string = "Hello, World!";

      struct kc_node_t* node_string = node_constructor(string, strlen(string) + 1);

      char* ptr_string = (char*)node_string->data;
      for (size_t i = 0; i < strlen(string); i++)
      {
        // verify with a pointer
        ok(ptr_string[i] == string[i]);

        // verify by direct access memory
        ok(((char*)node_string->data)[i] == string[i]);
      }

      node_destructor(node_string);
    }

    subtest("test long")
    {
      // initialize the node
      unsigned long long data_max = 184467440737095516;
      struct kc_node_t* node_max = node_constructor(&data_max, sizeof(data_max));

      // verify with a pointer
      unsigned long long* ptr_max = (unsigned long long*)node_max->data;
      ok(*ptr_max == data_max);

      // verify by direct access memory
      ok(*(unsigned long long*)node_max->data == 184467440737095516);

      node_destructor(node_max);
    }


    subtest("test costume type")
    {
      // Create a costumized test structure.
      struct Test {
        int key;
        char* value;
      };

      struct Test test = { 100, "test" };

      // initialize and access node data
      struct kc_node_t* node = node_constructor(&test, sizeof(struct Test));

      // verify with a pointer
      struct Test* ptr_customized = (struct Test*)node->data;
      ok(ptr_customized->key == test.key);
      ok(strcmp(ptr_customized->value, test.value) == 0);

      // verify by direct access memory
      ok(((struct Test*)node->data)->key == 100);
      ok(strcmp(((struct Test*)node->data)->value, "test") == 0);

      node_destructor(node);
    }

    done_testing()
  }

  testgroup("kc_pair_t")
  {
    subtest("test creation and destruction")
    {
      char key[] = "dummy";
      int value = 10000000;

      struct kc_pair_t* pair = pair_constructor(&key,
        strlen(key) + 1, &value, sizeof(int));

      ok(strcmp((char*)pair->key, key) == 0);
      ok(*(int*)pair->value == value);

      pair_destructor(pair);
    }

    subtest("test integer to integer")
    {
      int key = 1, value = 100;
      struct kc_pair_t* pair = pair_constructor(&key,
        sizeof(int), &value, sizeof(int));

      // Access the key and value
      ok(*(int*)pair->key == key);
      ok(*(int*)pair->value == value);

      pair_destructor(pair);
    }

    subtest("test integer to character")
    {
      int key = 2;
      char* value = "example";
      struct kc_pair_t* pair = pair_constructor(&key,
        sizeof(int), value, strlen(value) + 1);

      // Access the key and value
      ok(*(int*)pair->key == key);
      ok(strcmp((char*)pair->value, value) == 0);

      pair_destructor(pair);
    }

    subtest("test character to character")
    {
      char* key = "some_key";
      char* value = "example";
      struct kc_pair_t* pair = pair_constructor(key,
        strlen(key) + 1, value, strlen(value) + 1);

      // Access the key and value
      ok(strcmp((char*)pair->key, key) == 0);
      ok(strcmp((char*)pair->value, value) == 0);

      pair_destructor(pair);
    }

    subtest("test character to integer") {
      char* key = "key";
      int value = 400;
      struct kc_pair_t* pair = pair_constructor(key,
        strlen(key) + 1, &value, sizeof(int));

      // Access the key and value
      ok(strcmp((char*)pair->key, key) == 0);
      ok(*(int*)pair->value == value);

      pair_destructor(pair);
    }

    subtest("test primitive int array")
    {
      int key = 1;

      // test the array of integer (int[]) data type
      int nums[] = { 1, 2, 3, 4, 5 };
      size_t size_int = sizeof(nums) / sizeof(nums[0]);

      struct kc_pair_t* pair = pair_constructor(&key, sizeof(int),
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

      struct kc_pair_t* pair = pair_constructor(key, strlen(key),
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

      struct kc_pair_t* pair_max = pair_constructor(&key, sizeof(key),
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
      struct kc_pair_t* pair = pair_constructor(&key, sizeof(int),
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

  testgroup("kc_queue_t")
  {
    subtest("test init/desc")
    {
      struct kc_queue_t* queue = new_queue();

      ok(queue->_list->_head == NULL);

      destroy_queue(queue);
    }

    subtest("test length()")
    {
      // create a new instance of a Queue
      struct kc_queue_t* queue = new_queue();

      int ret = KC_INVALID;
      size_t length = 1;

      // the list should be empty
      ret = queue->length(queue, &length);

      ok(ret == KC_SUCCESS);
      ok(length == 0);

      // push ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = queue->push(queue, &i, sizeof(i));

        ok(ret == KC_SUCCESS);
      }

      // the list should be have 10 nodes
      ret = queue->length(queue, &length);

      ok(ret == KC_SUCCESS);
      ok(length == 10);

      // remove 4 nodes
      ret = queue->pop(queue);
      ok(ret == KC_SUCCESS);

      ret = queue->pop(queue);
      ok(ret == KC_SUCCESS);

      ret = queue->pop(queue);
      ok(ret == KC_SUCCESS);

      ret = queue->pop(queue);
      ok(ret == KC_SUCCESS);

      // the list should be have 6 nodes
      ret = queue->length(queue, &length);

      ok(ret == KC_SUCCESS);
      ok(length == 6);

      destroy_queue(queue);
    }

    subtest("test peek()")
    {
      // create a new instance of a Queue
      struct kc_queue_t* queue = new_queue();

      int ret = KC_INVALID;
      void* data = NULL;

      // push ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = queue->push(queue, &i, sizeof(i));

        ok(ret == KC_SUCCESS);
      }

      for (int i = 0; i < 10; ++i)
      {
        // check if the nodes have been peeked correctly
        ret = queue->peek(queue, &data);

        ok(ret == KC_SUCCESS);
        ok(*(int*)data == i);

        // destroy the first node
        ret = queue->pop(queue);

        ok(ret == KC_SUCCESS);
      }

      destroy_queue(queue);
    }

    subtest("test pop()")
    {
      // create a new instance of a Queue
      struct kc_queue_t* queue = new_queue();

      int ret = KC_INVALID;

      // push ten new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = queue->push(queue, &i, sizeof(i));

        ok(ret == KC_SUCCESS);
      }

      for (int i = 1; i < 10; ++i)
      {
        ret = queue->pop(queue);

        ok(ret == KC_SUCCESS);

        // check if the nodes have been removed correctly
        ok(queue->_list->length == 10 - i);
      }

      destroy_queue(queue);
    }

    subtest("test push")
    {
      // create a new instance of a Queue
      struct kc_queue_t* queue = new_queue();

      int ret = KC_INVALID;

      // push ten new nodes of type int
      for (int i = 0; i < 10; ++i)
      {
        ret = queue->push(queue, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check the length of the list
        ok(queue->_list->length == i + 1);
      }

      // push ten new nodes of type char
      for (int i = 10; i < 20; ++i)
      {
        char c = 'a' + i;
        ret = queue->push(queue, &c, sizeof(char));


        // check the length of the list
        ok(queue->_list->length == i + 1);
      }

      for (int i = 0; i < 20; ++i)
      {
        struct kc_node_t* cursor = queue->_list->_head;
        for (int j = 0; j < i; ++j)
        {
          cursor = cursor->next;
        }

        // check if the nodes have been inserted correctly
        if (i < 10)
        {
          ok(*(int*)cursor->data == i);
        }
        else
        {
          ok(*(char*)cursor->data == 'a' + i);
        }
      }

      // add a new node of type int[] (array)
      int nums[] = { 1, 2, 3, 4, 5 };
      size_t size = sizeof(nums) / sizeof(nums[0]);
      ret = queue->push(queue, &nums, sizeof(int) * size);

      ok(ret == KC_SUCCESS);

      // get the 21st node
      struct kc_node_t* cursor = queue->_list->_tail;

      // check if the node has been inserted correctly
      int* ptr = (int*)cursor->data;
      for (int i = 0; i < size; ++i)
      {
        ok(ptr[i] == nums[i]);
      }

      // add a new node of type Test (struct)
      struct Test
      {
        int key;
        char* value;
      };

      struct Test test = { 100, "example" };
      ret = queue->push(queue, &test, sizeof(struct Test));

      ok(ret == KC_SUCCESS);

      // get the 22st node
      cursor = queue->_list->_tail;

      ok((int)(((struct Test*)cursor->data)->key) == test.key);
      ok(strcmp((char*)(((struct Test*)cursor->data)->value), test.value) == 0);

      destroy_queue(queue);
    }

    done_testing()
  }

  testgroup("kc_set_t")
  {
    subtest("test init/desc")
    {
      struct kc_set_t* set = new_set(set_compare_int);

      ok(set->_entries->root == NULL);

      destroy_set(set);
    }

    subtest("test insert() & search()")
    {
      // create a new instance of a Set
      struct kc_set_t* set = new_set(set_compare_int);

      int ret = KC_INVALID;


      // insert ten new entries
      for (int i = 0; i < 10; ++i)
      {
        int val = i * 100;

        // use the "i" variable as the "key" and the "val" variable as the value
        ret = set->insert(set, &i, sizeof(int), &val, sizeof(int));
        ok(ret == KC_SUCCESS);
      }

      // search for the newlly created entries
      for (int i = 0; i < 10; ++i)
      {
        void* searchable = NULL;
        ret = set->search(set, &i, sizeof(int), &searchable);

        // check the data inserted
        ok(ret == KC_SUCCESS);
        ok(*(int*)searchable == i * 100);
      }

      // search again, but in reverse
      for (int i = 9; i >= 0; --i)
      {
        void* searchable = NULL;
        ret = set->search(set, &i, sizeof(int), &searchable);

        // check the data inserted
        ok(ret == KC_SUCCESS);
        ok(*(int*)searchable == i * 100);
      }

      destroy_set(set);
    }

    // Test case for remove() method
    subtest("test remove()")
    {
      struct kc_set_t* set = new_set(set_compare_int);

      int ret = KC_INVALID;

      // insert 10 new entries
      for (int i = 0; i < 10; ++i)
      {
        ret = set->insert(set, &i, sizeof(int), &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // remove the pair and check it's existance
      int pair_to_remove = 5;
      void* searchable = 0;

      ret = set->remove(set, &pair_to_remove, sizeof(int));
      ok(ret == KC_SUCCESS);

      ret = set->search(set, &pair_to_remove, sizeof(int), searchable);
      ok(searchable == NULL);

      pair_to_remove = 0;
      ret = set->remove(set, &pair_to_remove, sizeof(int));
      ok(ret == KC_SUCCESS);

      ret = set->search(set, &pair_to_remove, sizeof(int), searchable);
      ok(searchable == NULL);

      pair_to_remove = 9;
      ret = set->remove(set, &pair_to_remove, sizeof(int));
      ok(ret == KC_SUCCESS);

      ret = set->search(set, &pair_to_remove, sizeof(int), searchable);
      ok(searchable == NULL);

      destroy_set(set);
    }

    // Test comparing strings in the binary tree
    subtest("test str compare")
    {
      struct kc_set_t* set = new_set(set_compare_str);

      int ret = KC_INVALID;

      char key1[] = "1";
      char val1[] = "apple";
      ret = set->insert(set, &key1, strlen(key1) + 1, &val1, strlen(val1) + 1);
      ok(ret == KC_SUCCESS);

      char key2[] = "2";
      char val2[] = "banana";
      ret = set->insert(set, &key2, strlen(key2) + 1, &val2, strlen(val2) + 1);
      ok(ret == KC_SUCCESS);

      char key3[] = "3";
      char val3[] = "cherry";
      ret = set->insert(set, &key3, strlen(key3) + 1, &val3, strlen(val3) + 1);
      ok(ret == KC_SUCCESS);

      void* found = NULL;
      ret = set->search(set, &key1, strlen(key1) + 1, &found);
      ok(ret == KC_SUCCESS);
      ok(strcmp((char*)found, val1) == 0);

      ret = set->search(set, &key2, strlen(key2) + 1, &found);
      ok(ret == KC_SUCCESS);
      ok(strcmp((char*)found, val2) == 0);

      ret = set->search(set, &key3, strlen(key3) + 1, &found);
      ok(ret == KC_SUCCESS);
      ok(strcmp((char*)found, val3) == 0);

      destroy_set(set);
    }

    done_testing()
  }

  testgroup("kc_tree_t")
  {
    subtest("test init/desc")
    {
      struct kc_tree_t* tree = new_tree(btree_compare_int);

      ok(tree->root == NULL);

      destroy_tree(tree);
    }

    subtest("test insert() & search()")
    {
      struct kc_tree_t* tree = new_tree(btree_compare_int);

      int ret = KC_INVALID;

      // insert 30 new nodes
      for (int data = 0; data < 30; ++data)
      {
        ret = tree->insert(tree, &data, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // search for the newlly created nodes
      for (int data = 0; data < 30; ++data)
      {
        struct kc_node_t* found_node = NULL;
        ret = tree->search(tree, &data, &found_node);

        ok(ret == KC_SUCCESS);

        // check the data inserted
        ok(found_node != NULL);
        ok(*(int*)found_node->data == data);
      }

      // search again, but in reverse
      for (int data = 29; data >= 0; --data)
      {
        struct kc_node_t* found_node = NULL;
        ret = tree->search(tree, &data, &found_node);

        ok(ret == KC_SUCCESS);

        // check the data inserted
        ok(found_node != NULL);
        ok(*(int*)found_node->data == data);
      }

      destroy_tree(tree);
    }

    subtest("test remove")
    {
      struct kc_tree_t* tree = new_tree(btree_compare_int);
      int data[] = { 50, 30, 60, 20, 70, 15, 75, 25, 65 };

      int ret = KC_INVALID;

      // insert nodes for all test cases
      for (int i = 0; i < 9; ++i)
      {
        ret = tree->insert(tree, &data[i], sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // test case 1: remove node with 2 children
      int remove = 20;
      ret = tree->remove(tree, &remove, sizeof(int));
      ok(ret == KC_SUCCESS);

      struct kc_node_t* found_node = tree->root->prev->prev;
      ok(*(int*)found_node->data == 25);
      ok(*(int*)found_node->prev->data == 15);
      ok(found_node->next == NULL);

      // test case 2: remove node with 1 child
      remove = 60;
      ret = tree->remove(tree, &remove, sizeof(int));
      ok(ret == KC_SUCCESS);

      found_node = tree->root->next;
      ok(*(int*)found_node->data == 70);
      ok(*(int*)found_node->prev->data == 65);
      ok(*(int*)found_node->next->data == 75);

      // test case 3: remove node with 0 children
      remove = 75;
      ret = tree->remove(tree, &remove, sizeof(int));
      ok(ret == KC_SUCCESS);

      found_node = tree->root->next;
      ok(*(int*)found_node->data == 70);
      ok(*(int*)found_node->prev->data == 65);
      ok(found_node->next == NULL);

      // test case 4: remove root node
      remove = 50;
      ret = tree->remove(tree, &remove, sizeof(int));
      ok(ret == KC_SUCCESS);

      found_node = tree->root;
      ok(*(int*)found_node->data == 65);
      ok(*(int*)found_node->prev->data == 30);
      ok(*(int*)found_node->next->data == 70);

      destroy_tree(tree);
    }

    subtest("test str compare")
    {
      struct kc_tree_t* tree = new_tree(btree_compare_str);

      int ret = KC_INVALID;

      char* data1 = "apple";
      char* data2 = "banana";
      char* data3 = "cherry";

      ret = tree->insert(tree, data1, strlen(data1) + 1);
      ok(ret == KC_SUCCESS);

      ret = tree->insert(tree, data2, strlen(data2) + 1);
      ok(ret == KC_SUCCESS);

      ret = tree->insert(tree, data3, strlen(data3) + 1);
      ok(ret == KC_SUCCESS);

      struct kc_node_t* found_node1 = NULL;
      ret = tree->search(tree, data1, &found_node1);

      struct kc_node_t* found_node2 = NULL;
      ret = tree->search(tree, data2, &found_node2);

      struct kc_node_t* found_node3 = NULL;
      ret = tree->search(tree, data3, &found_node3);

      ok(found_node1 != NULL);
      ok(strcmp(found_node1->data, data1) == 0);

      ok(found_node2 != NULL);
      ok(strcmp(found_node2->data, data2) == 0);

      ok(found_node3 != NULL);
      ok(strcmp(found_node3->data, data3) == 0);

      destroy_tree(tree);
    }

    subtest("test custom compare")
    {
      struct kc_tree_t* tree = new_tree(test_tree_compare);

      // create a new Pair
      int key = 10, val = 100;
      struct kc_pair_t* pair = pair_constructor(&key, sizeof(int), &val, sizeof(int));

      int ret = KC_INVALID;

      // insert the new pair
      ret = tree->insert(tree, pair, sizeof(struct kc_pair_t));
      ok(ret == KC_SUCCESS);

      // check if the pair was inserted and found corectlly
      struct kc_node_t* found_node = NULL;
      ret = tree->search(tree, pair, &found_node);
      ok(ret == KC_SUCCESS);

      struct kc_pair_t* found_pair = (struct kc_pair_t*)found_node->data;

      ok(found_pair != NULL);
      ok(*(int*)found_pair->key == key);
      ok(*(int*)found_pair->value == val);

      // check the remove function
      ret = tree->remove(tree, pair, sizeof(struct kc_pair_t));
      ok(ret == KC_SUCCESS);
      ok(tree->root == NULL);

      pair_destructor(pair);
      destroy_tree(tree);
    }

    done_testing()
  }

  testgroup("kc_stack_t")
  {
    subtest("test init/desc")
    {
      struct kc_stack_t* stack = new_stack();

      ok(stack->_vector->length == 0);
      ok(stack->_vector->_capacity == 16);

      destroy_stack(stack);
    }

    subtest("test length()")
    {
      struct kc_stack_t* stack = new_stack();

      int ret = KC_INVALID;
      size_t length = 1;

      ret = stack->length(stack, &length);

      // the length should be zero
      ok(ret == KC_SUCCESS);
      ok(length == 0);

      // push 10 more items
      for (int i = 0; i < 10; ++i)
      {
        ret = stack->push(stack, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      ret = stack->length(stack, &length);

      ok(ret == KC_SUCCESS);
      ok(length == 10);

      stack->_vector->clear(stack->_vector);

      // should be empty again
      ret = stack->length(stack, &length);

      ok(ret == KC_SUCCESS);
      ok(length == 0);

      destroy_stack(stack);
    }

    subtest("test pop()")
    {
      struct kc_stack_t* stack = new_stack();

      int ret = KC_INVALID;

      // push 10 new nodes
      for (int i = 0; i < 10; ++i)
      {
        ret = stack->push(stack, &i, sizeof(i));

        ok(ret == KC_SUCCESS);
      }

      for (int i = 1; i < 10; ++i)
      {
        ret = stack->pop(stack);
        ok(ret == KC_SUCCESS);

        // check if the items have been removed correctly
        ok(stack->_vector->length == 10 - i);
      }

      destroy_stack(stack);
    }

    subtest("test push()")
    {
      struct kc_stack_t* stack = new_stack();

      int ret = KC_INVALID;

      // push 10 new items
      for (int i = 0; i < 10; ++i)
      {
        ret = stack->push(stack, &i, sizeof(i));
        ok(ret == KC_SUCCESS);

        // check the length of the list
        ok(stack->_vector->length == i + 1);
      }

      for (int i = 0; i < 10; ++i)
      {
        // check if the nodes have been pushed correctly
        ok(*(int*)stack->_vector->data[i] == i);
      }

      destroy_stack(stack);
    }

    subtest("test top()")
    {
      struct kc_stack_t* stack = new_stack();

      int ret = KC_INVALID;

      // push 60 more items
      for (int i = 0; i < 60; ++i)
      {
        ret = stack->push(stack, &i, sizeof(int));
        ok(ret == KC_SUCCESS);

        void* top = NULL;
        ret = stack->top(stack, &top);

        // check each new item
        ok(*(int*)top == i);
      }

      // check the capacity of the vector
      ok(stack->_vector->_capacity == 64);

      destroy_stack(stack);
    }

    done_testing()
  }

  testgroup("kc_vector_t")
  {
    subtest("test init/desc")
    {
      struct kc_vector_t* vector = new_vector();

      ok(vector->length == 0);
      ok(vector->_capacity == 16);

      destroy_vector(vector);
    }

    subtest("test at()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 10 new items
      for (int i = 0; i < 10; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // get and verify each element
      for (int i = 0; i < 10; ++i)
      {
        void* at = NULL;
        ret = vector->at(vector, i, &at);
        ok(ret == KC_SUCCESS);

        // check the values of the vector
        ok(*(int*)at == i);
      }

      destroy_vector(vector);
    }

    subtest("test back()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 10 new items and check the last element
      for (int i = 0; i < 10; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));
        ok(ret == KC_SUCCESS);

        void* back = NULL;
        ret = vector->back(vector, &back);
        ok(ret == KC_SUCCESS);
        ok(*(int*)back == i);
      }

      destroy_vector(vector);
    }

    subtest("test clear()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      ok(vector->length == 20);
      ok(vector->_capacity == 32);

      // clear and check again
      ret = vector->clear(vector);

      ok(ret == KC_SUCCESS);

      ok(vector->length == 0);
      ok(vector->_capacity == 16);

      // reuse the freed memory
      vector->data[4] = malloc(sizeof(int));
      *(int*)vector->data[4] = 10;
      ok(*(int*)vector->data[4] == 10);

      destroy_vector(vector);
    }

    subtest("test empty()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;
      bool empty = false;

      ret = vector->empty(vector, &empty);

      // the vector should be empty
      ok(ret == KC_SUCCESS);
      ok(empty == true);

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // the vector should not be empty
      ret = vector->empty(vector, &empty);
      ok(ret == KC_SUCCESS);
      ok(empty == false);

      ret = vector->clear(vector);
      ok(ret == KC_SUCCESS);

      // the vector should be empty again
      ret = vector->empty(vector, &empty);
      ok(ret == KC_SUCCESS);
      ok(empty == true);

      destroy_vector(vector);
    }

    subtest("test erase()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // erase the newly created items
      for (int i = 0; i < 10; ++i)
      {
        ret = vector->erase(vector, 10);
        ok(ret == KC_SUCCESS);

        // check the size
        ok(vector->length == 19 - i);

        // check that all the elements are still in the same order
        for (int j = 10; j < vector->length; ++j)
        {
          ok(*(int*)vector->data[j] == j + 1 + i);
        }
      }

      // if the length is less than half of the capacity,
      // should resize the max_size to half
      size_t max_size = 0;
      ret = vector->max_size(vector, &max_size);
      ok(ret == KC_SUCCESS);
      ok(max_size == 16);

      // erase the last elements
      for (int i = 0; i < 10; ++i)
      {
        ret = vector->erase(vector, 0);

        ok(ret == KC_SUCCESS);
      }

      ret = vector->max_size(vector, &max_size);
      ok(ret == KC_SUCCESS);
      ok(max_size == 16);

      bool empty = false;
      ret = vector->empty(vector, &empty);

      // the vector should be empty
      ok(ret == KC_SUCCESS);
      ok(empty == true);

      destroy_vector(vector);
    }

    subtest("test front()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 10 new items and check the last element
      for (int i = 0; i < 10; ++i)
      {
        ret = vector->insert(vector, 0, &i, sizeof(int));
        ok(ret == KC_SUCCESS);

        void* front = NULL;
        ret = vector->front(vector, &front);

        ok(*(int*)front == i);
      }

      destroy_vector(vector);
    }

    subtest("test insert()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check the size of the vector
        ok(vector->length == i + 1);

        // check the values of the vector
        ok(*(int*)vector->data[i] == i);
      }

      // check the capacity of the vector
      ok(vector->_capacity == 32);

      int data = 100;
      ret = vector->insert(vector, 10, &data, sizeof(int));
      ok(ret == KC_SUCCESS);

      data = 101;
      ret = vector->insert(vector, 11, &data, sizeof(int));
      ok(ret == KC_SUCCESS);

      data = 102;
      ret = vector->insert(vector, 12, &data, sizeof(int));
      ok(ret == KC_SUCCESS);

      // check the values of the vector
      ok(*(int*)vector->data[10] == 100);
      ok(*(int*)vector->data[11] == 101);
      ok(*(int*)vector->data[12] == 102);

      destroy_vector(vector);
    }

    subtest("test max_size()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      size_t max_size = 1;
      int ret = KC_INVALID;

      ret = vector->max_size(vector, &max_size);
      ok(ret == KC_SUCCESS);

      // check the capacity of the vector
      ok(vector->_capacity == max_size);
      ok(max_size == 16);

      // push 20 new items
      for (int i = 0; i < 20; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check the capacity of the vector
        if (i < 15) {
          ret = vector->max_size(vector, &max_size);

          ok(ret == KC_SUCCESS);
          ok(max_size == 16);

          continue;
        }

        ret = vector->max_size(vector, &max_size);

        ok(ret == KC_SUCCESS);
        ok(max_size == 32);
      }

      ret = vector->max_size(vector, &max_size);

      ok(ret == KC_SUCCESS);

      // check the capacity of the vector
      ok(vector->_capacity == max_size);
      ok(max_size == 32);

      destroy_vector(vector);
    }

    subtest("test pop_back()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 15 new items
      for (int i = 0; i < 15; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // erase the last elements
      for (int i = 0; i < 15; ++i)
      {
        // check the last element before poping
        ok(vector->length == 15 - i);

        void* back = NULL;
        ret = vector->back(vector, &back);

        ok(ret == KC_SUCCESS);
        ok(*(int*)back == 14 - i);

        ret = vector->pop_back(vector);

        ok(ret == KC_SUCCESS);
      }

      destroy_vector(vector);
    }

    subtest("test pop_front()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // push 15 new items
      for (int i = 0; i < 15; ++i)
      {
        ret = vector->insert(vector, i, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // erase the first elements
      for (int i = 0; i < 15; ++i)
      {
        // check the first element before poping
        ok(vector->length == 15 - i);

        void* front = NULL;
        ret = vector->front(vector, &front);

        ok(ret == KC_SUCCESS);
        ok(*(int*)front == i);

        ret = vector->pop_front(vector);

        ok(ret == KC_SUCCESS);
      }

      destroy_vector(vector);
    }

    subtest("test push_back()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      for (int i = 0; i < 10; ++i)
      {
        ret = vector->push_back(vector, &i, sizeof(int));

        ok(ret == KC_SUCCESS);

        // check the length and the data inserted
        ok(vector->length == i + 1);

        void* at = NULL;
        ret = vector->at(vector, vector->length - 1, &at);

        ok(ret == KC_SUCCESS);
        ok(*(int*)at == i);
      }

      destroy_vector(vector);
    }

    subtest("test push_front()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      for (int i = 0; i < 10; ++i)
      {
        ret = vector->push_front(vector, &i, sizeof(int));
        ok(ret == KC_SUCCESS);

        // check the length and the data inserted
        ok(vector->length == i + 1);

        void* at = NULL;
        ret = vector->at(vector, 0, &at);

        ok(ret == KC_SUCCESS);
        ok(*(int*)at == i);
      }

      destroy_vector(vector);
    }

    subtest("test remove()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // add 5 new elements
      int data = 10;
      for (int i = 0; i < 5; ++i)
      {
        ret = vector->push_back(vector, &data, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // add 5 more new elements
      data = 20;
      for (int i = 0; i < 5; ++i)
      {
        ret = vector->push_back(vector, &data, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // should remove only 5 elements
      ret = vector->remove(vector, &data, test_vector_compare);
      ok(ret == KC_SUCCESS);
      ok(vector->length == 5);

      data = 10;

      // should remove all 5 elements
      ret = vector->remove(vector, &data, test_vector_compare);
      ok(ret == KC_SUCCESS);

      bool empty = false;

      ret = vector->empty(vector, &empty);
      ok(ret == KC_SUCCESS);
      ok(empty == true);

      destroy_vector(vector);
    }

    subtest("test resize()")
    {
      // create a new instance of a List
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;
      size_t max_size = 0;

      ret = vector->max_size(vector, &max_size);

      // check the default capacity size
      ok(ret == KC_SUCCESS);
      ok(max_size == 16);

      // change the capacity and check it
      ret = vector->resize(vector, 64);
      ok(ret == KC_SUCCESS);

      ret = vector->max_size(vector, &max_size);
      ok(ret == KC_SUCCESS);
      ok(max_size == 64);

      ret = vector->resize(vector, 128);
      ok(ret == KC_SUCCESS);

      ret = vector->max_size(vector, &max_size);
      ok(ret == KC_SUCCESS);
      ok(max_size == 128);

      ret = vector->resize(vector, 16);
      ok(ret == KC_SUCCESS);

      ret = vector->max_size(vector, &max_size);
      ok(ret == KC_SUCCESS);
      ok(max_size == 16);

      destroy_vector(vector);
    }

    subtest("test search()")
    {
      // create a new instance of a vector
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // add 10 new elements
      for (int i = 0; i < 10; ++i) {
        ret = vector->push_back(vector, &i, sizeof(int));

        ok(ret == KC_SUCCESS);
      }

      // should return true
      int search_data = 3;
      bool exists = false;
      ret = vector->search(vector, &search_data, test_vector_compare, &exists);
      ok(ret == KC_SUCCESS);
      ok(exists == true);

      // should return true
      search_data = 8;
      ret = vector->search(vector, &search_data, test_vector_compare, &exists);
      ok(ret == KC_SUCCESS);
      ok(exists == true);

      // should return false
      search_data = 12;
      ret = vector->search(vector, &search_data, test_vector_compare, &exists);
      ok(ret == KC_SUCCESS);
      ok(exists == false);

      destroy_vector(vector);
    }

    subtest("test data types")
    {
      struct kc_vector_t* vector = new_vector();

      int ret = KC_INVALID;

      // test integer (int)
      int intValue = 42;
      ret = vector->insert(vector, vector->length, &intValue, sizeof(int));
      ok(ret == KC_SUCCESS);
      ok(*(int*)vector->data[0] == 42);

      // test real (double)
      double doubleValue = 3.14;
      ret = vector->insert(vector, vector->length, &doubleValue, sizeof(double));
      ok(ret == KC_SUCCESS);
      ok(*(double*)vector->data[1] == 3.14);

      // test character (char)
      char stringValue[] = "Hello, World!";
      ret = vector->insert(vector, vector->length, stringValue, sizeof(stringValue));
      ok(ret == KC_SUCCESS);
      ok(strcmp((char*)vector->data[2], "Hello, World!") == 0);

      // test custom data (struct)
      struct Test { int key; char* val; } test = { 10, "test" };
      ret = vector->insert(vector, vector->length, &test, sizeof(struct Test));
      ok(ret == KC_SUCCESS);

      struct Test* ptr = (struct Test*)vector->data[3];
      ok(strcmp(ptr->val, test.val) == 0);
      ok(ptr->key == test.key);

      destroy_vector(vector);
    }

    done_testing()
  }

  return 0;
}
