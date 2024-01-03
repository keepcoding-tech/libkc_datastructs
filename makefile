# This file is part of libkc_datastructs
# ==================================
#
# makefile
#
# Copyright (c) 2023 Daniel Tanase
# SPDX-License-Identifier: MIT License
#
#                  _         __ _ _
#                 | |       / _(_) |
#  _ __ ___   __ _| | _____| |_ _| | ___
# | '_ ` _ \ / _` | |/ / _ \  _| | |/ _ \
# | | | | | | (_| |   <  __/ | | | |  __/
# |_| |_| |_|\__,_|_|\_\___|_| |_|_|\___|
#

# Specify the compiler and compiler flags
CC     := gcc
STD    := -std=c99
CFLAGS := -Wall -Werror -Wpedantic -g -Iinclude

# Specify the source and the include directory
HDR_DIR  := include
SRC_DIR  := src
DEPS_DIR := deps

# Specify the source files and headers
SOURCES := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(HDR_DIR)/*.h)

# Specify the build directory
TMP_OBJ_DIR := build/tmp_obj
OBJ_DIR     := build/obj
BIN_DIR     := build/bin
TEST_DIR    := build/bin/test
LIB_OUT_DIR := build/lib

OBJ_DIRS := $(sort $(dir $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)))

# Static libraries in their directories
DEPS_STATIC_LIBS := deps/libkc/logger/libkc_logger.a

.PHONY: all build test clean help

##################################### ALL ######################################

all: clean build test

#################################### BUILD #####################################

build: $(EXTRACT_DEPS) $(OBJECTS) libkc_datastructs.a

# Extracted object files from the static libraries
EXTRACT_DEPS := $(patsubst $(DEPS_DIR)/%.a,$(TMP_EXTRACT_DIR)/%.o,$(DEPS_STATIC_LIBS))

$(TMP_EXTRACT_DIR)/%.o: $(DEPS_DIR)/%.a | $(TMP_EXTRACT_DIR)
	mkdir -p $(TMP_OBJ_DIR)$(TMP_EXTRACT_DIR)/$(basename $(notdir $<))
	cd $(TMP_OBJ_DIR)$(TMP_EXTRACT_DIR)/$(basename $(notdir $<)) && ar x $(addprefix ../../../, $<)

# Create a list of object files by replacing the file extensions
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJECTS): | $(OBJ_DIRS)

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

# Generic pattern rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(STD) $(CFLAGS) -c $< -o $@

libkc_datastructs.a: $(OBJECTS) $(EXTRACT_DEPS) | $(LIB_OUT_DIR)
	ar rcs $(LIB_OUT_DIR)/libkc_datastructs.a $(OBJECTS) $(shell find $(TMP_OBJ_DIR) -type f -name '*.o')

$(LIB_OUT_DIR):
	mkdir -p $(LIB_OUT_DIR)

##################################### TEST #####################################

# Extract the test file names from the source file names
TEST_FILES := $(basename $(notdir $(wildcard tests/*.c)))
TEST_TARGETS := $(addprefix $(TEST_DIR)/, $(TEST_FILES))
ALL_TESTS := $(addprefix $(TEST_DIR)/, $(TEST_FILES))

# Link all the static libraries for testing
TEST_STATIC_LIBS := kc_datastructs kc_testing
TEST_STATIC_LIBS_DIRS := build/lib deps/libkc/testing

LDFLAGS := $(addprefix -L, $(TEST_STATIC_LIBS_DIRS)) $(addprefix -l, $(TEST_STATIC_LIBS))

# Test command to run all test executables consecutively
test: $(TEST_TARGETS) $(ALL_TESTS)
	@for test_executable in $(ALL_TESTS); do \
		$$test_executable; \
	done

# Create the test directory
$(TEST_DIR):
	mkdir -p $(TEST_DIR)

# Define the SANITIZE variable to enable/disable AddressSanitizer
# Use `make SANITIZE=1` to enable AddressSanitizer, and `make` to disable it.
SANITIZE := 0
ifeq ($(SANITIZE), 1)
CFLAGS += -fsanitize=address
endif

# Dynamically generate the test targets and compile the test files
$(TEST_DIR)/%: tests/%.c | $(TEST_DIR)
	$(CC) $(STD) $(CFLAGS) $^ -o $@ $(LDFLAGS)

#################################### CLEAN #####################################

clean:
	rm -fr build *.o *.a

##################################### HELP #####################################

help:
	@echo "Available targets:"
	@echo "  all         : Compile the static library and all test executables"
	@echo "  build       : Compile the static library"
	@echo "  test        : Compile and run all test executables consecutively"
	@echo "  clean       : Clean up the object files and build directory"
	@echo "  help        : Display this help message"

