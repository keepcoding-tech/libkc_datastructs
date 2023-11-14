// This file is part of libkc_datastructs
// ==================================
//
// exceptions.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * This header file is private to the library and should not be included or
 * used by external developers. It is not part of the public API and is subject
 * to change without notice.
 *
 * This header file provides an exception handling framework through
 * enumerations and corresponding arrays of exception descriptions. It
 * encapsulates various types of exceptions that can occur during program
 * execution. Developers can use this framework to handle and report errors in
 * a structured manner.
 *
 * The EXCEPTION enumeration lists common exception types, and the exception and
 * log_exception arrays provide string representations and detailed descriptions
 * for each exception type, aiding in better error reporting and debugging.
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

enum EXCEPTION {
  EMPTY_STRUCTURE,
  INDEX_OUT_OF_BOUNDS,
  NULL_REFERENCE,
  OUT_OF_MEMORY,
  UNDERFLOW
};

const char* exception[] = {
  "EMPTY_STRUCTURE",
  "INDEX_OUT_OF_BOUNDS",
  "NULL_REFERENCE",
  "OUT_OF_MEMORY",
  "UNDERFLOW"
};

const char* log_exception[] = {
  "You are attempting to perform operations on an empty data structure",
  "You are trying to access an element at an invalid index in an array, list, "
    "or other indexed data structure.",
  "You are attempting to use a reference or pointer that points to null or is "
    "uninitialized.",
  "Failing to allocate memory dynamically (e.g. using malloc) due to "
    "insufficient memory in the heap.",
  "The data type's size goes below its minimum representable value."
};

#endif /* EXCEPTIONS_H */