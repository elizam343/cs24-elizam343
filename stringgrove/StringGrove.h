#ifndef STRINGGROVE_H
#define STRINGGROVE_H

// This file describes the STRINGGROVE interface you need to implement.
// Don't edit this!  Your code goes in the other files.

template <class T>
class StringGrove {
public:
  // Create and return a new string.
  static StringGrove* create(const char* s);

public:
  // These functions are "pure virtual" functions.
  // This means they're not implemented here, but your
  // subclass (MyGrove) is required to implement them.

  // How long is the string?
  virtual int len() const = 0;

  // Concatenate s onto the end of this string and return the new string.
  // This should take O(1) time.
  virtual const StringGrove* concat(T* s) const = 0;

  // Return the character at position i.
  // This can take O(h) time, where h is the number of concatenations.
  // If i is out of bounds, throw std::out_of_range.
  virtual char charAt(int i) const = 0;

  // Return the substring starting at position i and running up to
  // but not including position j.
  // If i or j is out of bounds or i > j, throw std::out_of_range.
  virtual const StringGrove* substr(int i, int j) const = 0;
};

#endif
