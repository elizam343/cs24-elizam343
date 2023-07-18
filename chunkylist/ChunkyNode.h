#ifndef CHUNKYNODE_H
#define CHUNKYNODE_H

#include <string>

// This file describes the ChunkyNode interface you need to implement.
// Don't edit this!  Your code goes in the .cpp files.

class ChunkyNode {
public:
  // Returns the number of items stored in this Node.
  virtual int count() const = 0;

  // Returns the items at this node as a C array.
  virtual std::string* items() const = 0;

  // Returns a pointer to the Node before this one, or nullptr.
  virtual ChunkyNode* prev() const = 0;

  // Returns a pointer to the Node after this one, or nullptr.
  virtual ChunkyNode* next() const = 0;

  // Don't forget!
  virtual ~ChunkyNode() {}
};

#endif
