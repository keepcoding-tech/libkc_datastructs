// This file is part of libkc_datastructs
// ==================================
//
// pair.h
//
// Copyright (c) 2023 Daniel Tanase
// SPDX-License-Identifier: MIT License

/*
 * Pairs serve as the fundamental units of sets and maps, comprising a value
 * that is stored and a key used for identification. This key-value structure
 * enables the storage of data of any type within the set.
 *
 * To properly deallocate a Pair, it is recommended to use the pair destructor.
 * This destructor will automatically free both the key-value pair and the Pair
 * itself.
 */

#ifndef PAIR_H
#define PAIR_H

#include <stdio.h>

struct Pair
{
  void* key;
  void* value;
};

struct Pair* pair_constructor  (void* key, size_t key_size, void* value, size_t value_size);
void         pair_destructor   (struct Pair* pair);

#endif /* PAIR_H */
