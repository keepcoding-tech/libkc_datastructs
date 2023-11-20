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
CC := gcc
STD := -std=c99
CFLAGS := -Wall -Werror -Wpedantic -g -Iinclude

# Specify the source and the include directory
HDR_DIR  := include
SRC_DIR  := src
DEPS_DIR := deps

# Specify the source files and headers
SOURCES := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(HDR_DIR)/*.h)

# Specify the build directory
OBJ_DIR  := build/obj
BIN_DIR  := build/bin
TEST_DIR := build/bin/test

OBJ_DIRS := $(sort $(dir $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)))

# Static libraries and their directories
STATIC_LIB_DIRS := $(wildcard $(DEPS_DIR)/*)
STATIC_LIBS := $(foreach dir, $(STATIC_LIB_DIRS), $(wildcard $(dir)/*.a))

.PHONY: all install test clean help

#################################### BUILD #####################################

# Create a list of object files by replacing the file extensions
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Set the default target
all: $(OBJECTS) libkc_datastructs.a

# Create the build directory and compile the object files
$(OBJECTS): | $(OBJ_DIRS)

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

# Generic pattern rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(STD) $(CFLAGS) -c $< -o $@

libkc_datastructs.a: $(OBJECTS)
	ar rcsT libkc_datastructs.a $(OBJECTS) $(STATIC_LIBS)

################################### INSTALL ####################################

install:
	@echo "Installing dependencies ..."
	git submodule update --init --recursive
	@echo "All dependencies have been installed!"
	@echo "Building dependencies..."
	@for submodule in $$(git submodule foreach --quiet 'echo $$path'); do \
		$(MAKE) -C $$submodule; \
	done

##################################### TEST #####################################

# Extract the test file names from the source file names
TEST_FILES := $(basename $(notdir $(wildcard tests/*.c)))

# Generate the test targets dynamically
TEST_TARGETS := $(addprefix $(TEST_DIR)/, $(TEST_FILES))

# Specify the list of all test executables
ALL_TESTS := $(addprefix $(TEST_DIR)/, $(TEST_FILES))

# Generate all the static libraries for testing
TEST_STATIC_LIBS := $(foreach dir, $(STATIC_LIB_DIRS), $(patsubst $(dir)/lib%.a,%,$(wildcard $(dir)/lib*.a)))
LDFLAGS := $(addprefix -L, $(STATIC_LIB_DIRS)) $(addprefix -l, $(TEST_STATIC_LIBS))

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
$(TEST_DIR)/%: tests/%.c $(OBJECTS) | $(TEST_DIR)
	$(CC) $(STD) $(CFLAGS) $^ -o $@ $(LDFLAGS)

#################################### CLEAN #####################################

clean:
	rm -fr build *.o *.a

##################################### HELP #####################################

# Help command to display available targets
help:
	@echo "Available targets:"
	@echo "  all         : Compile all test executables"
	@echo "  install     : Install all submodules dependencies"
	@echo "  test        : Run all test executables consecutively"
	@echo "  clean       : Clean up the object files and build directory"
	@echo "  help        : Display this help message"

