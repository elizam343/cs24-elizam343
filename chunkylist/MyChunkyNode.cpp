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

  // Shift elements to remove the item
  for (int i = index; i < current_count - 1; i++) {
    itemsArray[i] = itemsArray[i + 1];
  }
  itemsArray[current_count - 1].clear();
  decrementCount(); // if your count() is based on a variable, decrement it here
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
  // Only merge if the previous node exists and the total number of items in this node and the previous node is less or equal to chunksize / 2
  if (prevNode && count() + prevNode->count() <= chunkyNodeSize / 2) {
    // Move items from this node to the previous node
    for (int i = 0; i < count(); i++) {
      prevNode->itemsArray[prevNode->count() + i] = itemsArray[i];
      itemsArray[i].clear();  // clear the element after moving
    }

    // Adjust the count variables
    prevNode->countVariable += countVariable;
    countVariable = 0;  // set the count of the current node to 0

    // Update the next and prev pointers
    prevNode->setNext(nextNode);
    if (nextNode) {
      nextNode->setPrev(prevNode);
    }
    delete this;
  }
}
