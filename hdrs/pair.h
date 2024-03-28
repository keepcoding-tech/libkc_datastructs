// This file is part of keepcoding_core
// ==================================
//
// pair.h
//
// Copyright (c) 2024 Daniel Tanase
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

#ifndef KC_PAIR_T_H
#define KC_PAIR_T_H

#include "../system/logger.h"

#include <stdio.h>

//---------------------------------------------------------------------------//

#define KC_PAIR_LOG_PATH  "build/log/pair.log"

//---------------------------------------------------------------------------//

struct kc_pair_t
{
  void* key;
  void* value;
};

struct kc_pair_t* pair_constructor  (void* key, size_t key_size, void* value, size_t value_size);
void              pair_destructor   (struct kc_pair_t* pair);

//---------------------------------------------------------------------------//

#endif /* KC_PAIR_T_H */
