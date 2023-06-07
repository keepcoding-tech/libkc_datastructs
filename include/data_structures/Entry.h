// open source c library
// ==================================
//
// Entry.h
//
// Daniel Tanase
// 15/1/22

/*
 Entries are the fundamental unit of a sets, containing a value to be stored
 and a key to identify it, allowing any data type to be stored.
*/

#ifndef Entry_h
#define Entry_h

struct Entry {
  void *key;
  void *value;
};

// MARK: CONSTRUCTORS

// The constructor should be used to create Entries.
struct Entry entry_constructor(void *key, unsigned long key_size,
  void *value, unsigned long value_size);
// The destructor should be used to destroy a Entries.
void entry_destructor(struct Entry *entry);

#endif /* Entry_h */
