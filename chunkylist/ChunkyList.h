#ifndef CHUNKYLIST_H
#define CHUNKYLIST_H

#include "ChunkyNode.h"

// This file describes the ChunkyList interface you need to implement.
// Don't edit this!  Your code goes in the .cpp files.

class ChunkyList {
public:
  // Allocates a new list with the given chunk size.
  static ChunkyList* create(int chunksize);

public:
  // Returns the number of items (not Nodes) in the list.
  virtual int count() const = 0;

  // Returns a pointer to the first Node in the list, or nullptr.
  virtual ChunkyNode* head() const = 0;

  // Returns a pointer to the last Node in the list, or nullptr.
  virtual ChunkyNode* tail() const = 0;

  // Inserts an item at index.
  // Throws std::out_of_range if index is negative or > count().
  virtual void insert(int index, const std::string& item) = 0;

  // Returns a reference to the item at index.
  // Throws std::out_of_range if there is no such item.
  virtual std::string& lookup(int index) = 0;

  // Removes the item at index.
  // Throws std::out_of_range if there is no such item.
  virtual void remove(int index) = 0;

  // Don't forget!
  virtual ~ChunkyList() {}
};

#endif
