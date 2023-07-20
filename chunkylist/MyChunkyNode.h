#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"
#include <string>

class MyChunkyNode: public ChunkyNode {
  // TODO: Add any member variables you need.
private:
  int chunkSize;
  int itemCount;
  std::string* itemList;
  MyChunkyNode* prevNode;
  MyChunkyNode* nextNode;

public:
  // TODO: Constructor(s)
  // TODO: Destructor

  // These functions are needed by the autograder.
  // See ChunkyNode.h for their descriptions.
  int           count() const;
  std::string*  items() const;
  MyChunkyNode* prev()  const;
  MyChunkyNode* next()  const;
  void insert(int index, const std::string& item);
  void remove(int index);
  ~MyChunkyNode() override;

  // TODO: Add any other member functions you need.
};

#endif
