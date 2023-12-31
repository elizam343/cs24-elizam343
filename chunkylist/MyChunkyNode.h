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
  int countVariable;    

public:
  MyChunkyNode(int chunksize = 1);
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

  void split();
  void merge();
  void decrementCount();
  void append(const std::string& item);
  std::string get(int index);
  void shiftRight(int startIdx);
  void shiftLeft(int startIdx);
  void insertInCurrentNode(int index, const std::string& item);
  void splitAndInsert(int index, const std::string& item);
  MyChunkyNode* createNewNode();

};

#endif