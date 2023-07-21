#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode(int chunksize)
    : itemsArray(new std::string[chunksize]),
      prevNode(nullptr),
      nextNode(nullptr),
      chunkyNodeSize(chunksize) {
  // Initialize the items_ array to empty strings
  for (int i = 0; i < chunkyNodeSize; i++) {
    itemsArray[i] = "";
  }
}

MyChunkyNode::~MyChunkyNode() {
  delete[] itemsArray;
}

int MyChunkyNode::count() const {
  int count = 0;
  while (count < chunkyNodeSize && !itemsArray[count].empty())
    count++;
  return count;
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

void MyChunkyNode::insert(int index, const std::string& item) {
  int current_count = count();

  if (current_count < chunkyNodeSize) {
    for (int i = current_count; i > index; i--) {
      itemsArray[i] = itemsArray[i - 1];
    }
    itemsArray[index] = item;
  } else {
    int new_chunksize = chunkyNodeSize / 2;
    MyChunkyNode* new_node = new MyChunkyNode(new_chunksize);

    for (int i = 0; i < new_chunksize; i++) {
      new_node->itemsArray[i] = itemsArray[chunkyNodeSize - new_chunksize + i];
      itemsArray[chunkyNodeSize - new_chunksize + i].clear();
    }

    new_node->setNext(nextNode);
    new_node->setPrev(this);
    if (nextNode) {
      nextNode->setPrev(new_node);
    }
    setNext(new_node);

    if (index >= new_chunksize) {
      new_node->insert(index - new_chunksize, item);
    } else {
      insert(index, item);
    }
  }
}

void MyChunkyNode::remove(int index) {
  int current_count = count();

  if (current_count > 0) {
    // Shift elements to remove the item
    for (int i = index; i < current_count - 1; i++) {
      itemsArray[i] = itemsArray[i + 1];
    }
    itemsArray[current_count - 1].clear();

    // Check if the node can be merged with the previous node
    if (prevNode && prevNode->count() + current_count <= chunkyNodeSize) {
      for (int i = 0; i < current_count; i++) {
        prevNode->itemsArray[prevNode->count() + i] = itemsArray[i];
        itemsArray[i].clear();
      }
      prevNode->setNext(nextNode);
      if (nextNode) {
        nextNode->setPrev(prevNode);
      }
      delete this;
    }
  }
}

