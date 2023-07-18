#ifndef MYCHUNKYLIST_H
#define MYCHUNKYLIST_H

#include "ChunkyList.h"
#include "MyChunkyNode.h"

class MyChunkyList: public ChunkyList {
  // TODO: Add any member variables you need.
public:
  MyChunkyList(int chunksize);
  ~MyChunkyList();

  // These functions implement the Sequence abstract data type:
  // See ChunkyList.h for their descriptions.
  int          count() const;
  void         insert(int index, const std::string& item);
  std::string& lookup(int index);
  void         remove(int index);

  // These functions are needed by the autograder:
  MyChunkyNode* head() const;
  MyChunkyNode* tail() const;

  // TODO: Add any other member functions you need.
};

#endif
