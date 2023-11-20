// This file is part of libkc_datastructs
// ==================================
//
// exceptions.c
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

const char* err[] = 
{
  "EMPTY_STRUCTURE",
  "INDEX_OUT_OF_BOUNDS",
  "NULL_REFERENCE",
  "OUT_OF_MEMORY",
  "UNDERFLOW"
};

const char* log_err[] = 
{
  "You are attempting to perform operations on an empty data structure",
  "You are trying to access an element at an invalid index in an array, list, "
    "or other indexed data structure.",
  "You are attempting to use a reference or pointer that points to null or is "
    "uninitialized.",
  "Failing to allocate memory dynamically (e.g. using malloc) due to "
    "insufficient memory in the heap.",
  "The data type's size goes below its minimum representable value."
};
