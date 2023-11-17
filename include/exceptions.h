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
  KC_ERROR_EMPTY_STRUCTURE,
  KC_ERROR_INDEX_OUT_OF_BOUNDS,
  KC_ERROR_NULL_REFERENCE,
  KC_ERROR_OUT_OF_MEMORY,
  KC_ERROR_UNDERFLOW
};

extern const char* err[];

extern const char* log_err[];

#endif /* EXCEPTIONS_H */
