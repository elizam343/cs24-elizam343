#include "MyChunkyList.h"

// TODO: Member Function Implementation
MyChunkyList::MyChunkyList(int chunkSize) : chunkSize(chunkSize), headNode(nullptr), tailNode(nullptr), itemCount(0) {}

int MyChunkyList::count() const {
    return itemCount;
}

ChunkyNode* MyChunkyList::head() const {
    return headNode;
}

ChunkyNode* MyChunkyList::