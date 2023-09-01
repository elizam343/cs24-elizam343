#include "MyChunkyNode.h"
#include <stdexcept>

MyChunkyNode::MyChunkyNode(int chunksize)
    : itemsArray(new std::string[chunksize]),
      prevNode(nullptr),
      nextNode(nullptr),
      chunkyNodeSize(chunksize),
      countVariable(0) {}

MyChunkyNode::~MyChunkyNode() {
  delete[] itemsArray;
  itemsArray = nullptr;
}

int MyChunkyNode::count() const {
    return countVariable;
}

std::string* MyChunkyNode::items() const {
    return itemsArray;
}

MyChunkyNode* MyChunkyNode::prev() const {
    return prevNode;
}

MyChunkyNode* MyChunkyNode::next() const {
    return nextNode;
}

void MyChunkyNode::setPrev(MyChunkyNode* prev) {
    prevNode = prev;
}

void MyChunkyNode::setNext(MyChunkyNode* next) {
    nextNode = next;
}

// Helper function to create a new node
MyChunkyNode* MyChunkyNode::createNewNode() {
    MyChunkyNode* newNode = new MyChunkyNode(chunkyNodeSize);
    return newNode;
}

void MyChunkyNode::shiftRight(int startIdx) {
    for (int i = countVariable; i > startIdx; --i) {
        itemsArray[i] = itemsArray[i - 1];
    }
}

void MyChunkyNode::shiftLeft(int startIdx) {
    for (int i = startIdx; i < countVariable - 1; ++i) {
        itemsArray[i] = itemsArray[i + 1];
    }
}

void MyChunkyNode::insertInCurrentNode(int index, const std::string& item) {
    if (countVariable < chunkyNodeSize) {
        shiftRight(index);
        itemsArray[index] = item;
        ++countVariable;
    } else {
        // Handle node full case separately
        splitAndInsert(index, item);
    }
}

void MyChunkyNode::splitAndInsert(int index, const std::string& item) {
    MyChunkyNode* newNode = createNewNode();
    int remainingInCurrent = (countVariable + 1) / 2;

    if (index < remainingInCurrent) {
        for (int i = index; i < countVariable; ++i) {
            newNode->append(itemsArray[i]);
        }
        countVariable = index;
        this->insert(index, item);
    } else {
        for (int i = remainingInCurrent; i < countVariable; ++i) {
            newNode->append(itemsArray[i]);
        }
        countVariable = remainingInCurrent;
        newNode->insert(index - remainingInCurrent, item);
    }

    newNode->setNext(this->next());
    if (newNode->next() != nullptr) {
        newNode->next()->setPrev(newNode);
    }
    this->setNext(newNode);
    newNode->setPrev(this);
}

void MyChunkyNode::insert(int index, const std::string& item) {
    if (index < 0 || index > countVariable) {
        throw std::out_of_range("Index out of range");
    }
    insertInCurrentNode(index, item);
}

void MyChunkyNode::remove(int index) {
    if (index < 0 || index >= countVariable) {
        throw std::out_of_range("Index out of range");
    }

    shiftLeft(index);
    --countVariable;

    if (countVariable < chunkyNodeSize / 2 && nextNode && nextNode->countVariable > 0) {
        merge();
    }
}

void MyChunkyNode::append(const std::string& item) {
    if (countVariable < chunkyNodeSize) {
        itemsArray[countVariable] = item;
        ++countVariable;
    } else {
        throw std::runtime_error("Node is full");
    }
}

std::string MyChunkyNode::get(int index) {
    if (index >= 0 && index < countVariable) {
        return itemsArray[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

void MyChunkyNode::merge() {
    if (nextNode && (countVariable + nextNode->countVariable) <= chunkyNodeSize) {
        for (int i = 0; i < nextNode->countVariable; i++) {
            if (countVariable + i >= chunkyNodeSize) {
                throw std::runtime_error("Overflowing itemsArray during merge");
            }
            itemsArray[countVariable + i] = nextNode->itemsArray[i];
        }
        countVariable += nextNode->countVariable;
        
        MyChunkyNode* nodeToDelete = nextNode;
        nextNode = nodeToDelete->next();
        if (nextNode) {
            nextNode->setPrev(this);
        }
        delete nodeToDelete;
        nodeToDelete = nullptr;
    }
}
