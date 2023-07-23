#include "MyChunkyNode.h"
#include <stdexcept>

MyChunkyNode::MyChunkyNode(int chunksize)
    : itemsArray(new std::string[chunksize]),
      prevNode(nullptr),
      nextNode(nullptr),
      chunkyNodeSize(chunksize) {}

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
  if (index < 0 || index > current_count) {
    throw std::out_of_range("Index out of range.");
  }

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

    // update the current count after splitting
    current_count = count();
    if (index >= current_count) {
      new_node->insert(index - current_count, item);
    } else {
      for (int i = current_count; i > index; i--) {
        itemsArray[i] = itemsArray[i - 1];
      }
      itemsArray[index] = item;
    }
  }
}


void MyChunkyNode::remove(int index) {
  int current_count = count();
  if (index < 0 || index >= current_count) {
    throw std::out_of_range("Index out of range.");
  }

  if (current_count > 0) {
    // Shift elements to remove the item
    for (int i = index; i < current_count - 1; i++) {
      itemsArray[i] = itemsArray[i + 1];
    }
    itemsArray[current_count - 1].clear();
    decrementCount(); // if your count() is based on a variable, decrement it here

    current_count = count();
    // Check if the node can be merged with the previous node
    if (prevNode && prevNode->count() + current_count <= chunkyNodeSize) {
      for (int i = 0; i < current_count; i++) {
        prevNode->itemsArray[prevNode->count() + i] = itemsArray[i];
        itemsArray[i].clear();
        decrementCount(); // if your count() is based on a variable, decrement it here
      }
      prevNode->setNext(nextNode);
      if (nextNode) {
        nextNode->setPrev(prevNode);
      }
      delete this;
    }
  }
}

void MyChunkyNode::decrementCount() {
    if (countVariable > 0) // assuming countVariable is the variable tracking the number of items
        countVariable--;
}


void MyChunkyNode::split() {
  int current_count = count();
  if (current_count > chunkyNodeSize / 2) {
    int split_index = (current_count % 2 == 0) ? current_count / 2 : current_count / 2 + 1;

    MyChunkyNode* new_node = new MyChunkyNode(chunkyNodeSize);

    // Move items from the current node to the new node
    for (int i = split_index; i < chunkyNodeSize; i++) {
      new_node->itemsArray[i - split_index] = itemsArray[i];
      itemsArray[i] = ""; // Clear the item in the original array
    }

    // Adjust the count variables
    countVariable = split_index;
    new_node->countVariable = current_count - split_index;

    // Update the next and prev pointers
    new_node->setNext(nextNode);
    new_node->setPrev(this);
    if (nextNode) {
      nextNode->setPrev(new_node);
    }
    setNext(new_node);
  }
}

void MyChunkyNode::merge() {
  int current_count = count();
  if (current_count == 0 && prevNode && nextNode &&
      prevNode->count() + nextNode->count() <= chunkyNodeSize) {
    for (int i = 0; i < nextNode->count(); i++) {
      int source_index_prev = prevNode->count() + i;
      int source_index_next = i;
      if (source_index_prev >= 0 && source_index_prev < chunkyNodeSize &&
          source_index_next >= 0 && source_index_next < chunkyNodeSize &&
          !nextNode->itemsArray[source_index_next].empty()) {
        prevNode->itemsArray[source_index_prev] = nextNode->itemsArray[source_index_next];
        nextNode->itemsArray[source_index_next].clear();
      }
    }
    prevNode->setNext(nextNode->next());
    if (nextNode->next()) {
      nextNode->next()->setPrev(prevNode);
    }
    delete nextNode;
  }
}