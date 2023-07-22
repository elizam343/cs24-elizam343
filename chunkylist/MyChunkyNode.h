#ifndef MYCHUNKYNODE_H
#define MYCHUNKYNODE_H

#include "ChunkyNode.h"

class MyChunkyNode : public ChunkyNode {
private:
    std::string* itemsArray;
    MyChunkyNode* prevNode;
    MyChunkyNode* nextNode;
    int chunkyNodeSize;

public:
    MyChunkyNode(int chunksize);
    ~MyChunkyNode();

    int count() const;
    std::string* items() const;
    MyChunkyNode* prev() const;
    MyChunkyNode* next() const;

    void setPrev(MyChunkyNode* prev);
    void setNext(MyChunkyNode* next);
    void insert(int index, const std::string& item);
    void remove(int index);

    // Helper function to split the node
    void splitNode();
    // Helper function to merge with the next node
    void mergeNext();
};

#endif