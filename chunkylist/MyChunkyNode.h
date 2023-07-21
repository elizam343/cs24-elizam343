#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H
using namespace std;

#include "ChunkyNode.h"

class MyChunkyNode: public ChunkyNode {
private:
  string* itemsArray;   
  MyChunkyNode* prevNode;   
  MyChunkyNode* nextNode;   
  int chunkyNodeSize;        

public:
  MyChunkyNode(int chunksize);
  ~MyChunkyNode();


  // These functions are needed by the autograder.
  // See ChunkyNode.h for their descriptions.
  int           count() const;
  std::string*  items() const;
  MyChunkyNode* prev()  const;
  MyChunkyNode* next()  const;

  void setPrev(MyChunkyNode* prev);
  void setNext(MyChunkyNode* next);
  void insert(int index, const std::string& item);
  void remove(int index);
};

#endif
