#include "MyChunkyNode.h"

// TODO: Member Function Implementation
MyChunkyNode::MyChunkyNode(int chunkSize) : chunkSize(chunkSize), itemCount(0), itemList(nullptr), prevNode(nullptr), nextNode(nullptr) {
    itemList = new std::string[chunkSize];
}

int MyChunkyNode::count() const {
    return itemCount;
}

std::string* MyChunkyNode::items() const {
    return itemList;
}

ChunkyNode* MyChunkyNode::prev() const {
    return prevNode;
}

ChunkyNode* MyChunkyNode::next() const {
    return nextNode;
}

void MyChunkyNode::insert(int index, const std::string& item) {
    if (index < 0 || index > itemCount) {
        throw std::out_of_range("Invalid index.");
    }

    if (itemCount < chunkSize) {
        for (int i = itemCount; i > index; --i) {
            itemList[i] = itemList[i - 1];
        }
        itemList[index] = item;
        itemCount++;
    } else {
        MyChunkyNode* newNode = new MyChunkyNode(chunkSize);

        if (index == itemCount) {
            newNode->nextNode = nextNode;
            newNode->prevNode = this;
            if (nextNode) {
                nextNode->prevNode = newNode;
            }
            nextNode = newNode;
        } else {
            for (int i = chunkSize - 1; i > index; --i) {
                newNode->itemList[i - chunkSize] = itemList[i];
            }
            newItemList[index - chunkSize] = item;

            for (int i = index; i < chunkSize; ++i) {
                itemList[i] = "";
            }

            itemCount = chunkSize / 2 + 1;
            newNode->itemCount = chunkSize / 2;
            newNode->nextNode = nextNode;
            newNode->prevNode = this;
            nextNode = newNode;
            if (nextNode) {
                nextNode->prevNode = newNode;
            }
        }
    }
}

void MyChunkyNode::remove(int index) {
    if (index < 0 || index >= itemCount) {
        throw std::out_of_range("Invalid index.");
    }

    for (int i = index; i < itemCount - 1; ++i) {
        itemList[i] = itemList[i + 1];
    }

    itemList[itemCount - 1] = "";
    itemCount--;

    if (itemCount == 0) {
        if (prevNode) {
            prevNode->nextNode = nextNode;
        }
        if (nextNode) {
            nextNode->prevNode = prevNode;
        }
        delete this;
    } else if (prevNode && prevNode->count() + itemCount <= chunkSize / 2) {
        for (int i = 0; i < itemCount; ++i) {
            prevNode->itemList[prevNode->count()] = itemList[i];
            itemList[i] = "";
        }

        prevNode->itemCount += itemCount;
        prevNode->nextNode = nextNode;

        if (nextNode) {
            nextNode->prevNode = prevNode;
        }

        delete this;
    } else if (nextNode && nextNode->count() + itemCount <= chunkSize / 2) {
        for (int i = 0; i < nextNode->count(); ++i) {
            itemList[itemCount + i] = nextNode->itemList[i];
            nextNode->itemList[i] = "";
        }

        itemCount += nextNode->count();
        nextNode = nextNode->nextNode;

        if (nextNode) {
            nextNode->prevNode = this;
        }

        delete nextNode;
    }
}

MyChunkyNode::~MyChunkyNode() {
    delete[] itemList;
}