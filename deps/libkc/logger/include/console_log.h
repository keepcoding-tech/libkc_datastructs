// This file is part of libkc_logger
// ==================================
//
// console_log.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * The ConsoleLog structure, provides a generic logging mechanism with various
 * functionalities. It allows users to log messages with additional contextual
 * information such as file name, line number, and function name. The structure
 * contains function pointers for different logging operations.
 *
 * It is designed to enhance debugging and error reporting by providing
 * context-specific information for each logged message.
 */

#ifndef CONSOLE_LOG_H
#define CONSOLE_LOG_H

#include <stdio.h>
#include <stdlib.h>

struct ConsoleLog
{
  const char** exceptions;
  const char** descriptions;
  const char* file;

  void (*debug)    (struct ConsoleLog* self, const int index, const int line, const char* func);
  void (*error)    (struct ConsoleLog* self, const int index, const int line, const char* func);
  void (*fatal)    (struct ConsoleLog* self, const int index, const int line, const char* func);
  void (*info)     (struct ConsoleLog* self, const int index, const int line, const char* func);
  void (*warning)  (struct ConsoleLog* self, const int index, const int line, const char* func);
};

//---------------------------------------------------------------------------//

struct ConsoleLog* new_console_log      (const char** exceptions, const char** descriptions, const char* file);
void               destroy_console_log  (struct ConsoleLog* log);

//---------------------------------------------------------------------------//

void log_debug    (const char* title, const char* description, const char* file, const int line, const char* func);
void log_error    (const char* exception, const char* description, const char* file, const int line, const char* func);
void log_fatal    (const char* exception, const char* description, const char* file, const int line, const char* func);
void log_info     (const char* title, const char* description, const char* file, const int line, const char* func);
void log_warning  (const char* warning, const char* description, const char* file, const int line, const char* func);

#endif /* CONSOLE_LOG_H */
