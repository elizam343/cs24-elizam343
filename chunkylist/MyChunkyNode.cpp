#include "MyChunkyNode.h"
#include <stdexcept>

MyChunkyNode::MyChunkyNode(int chunksize)
    : itemsArray(new std::string[chunksize]),
      prevNode(nullptr),
      nextNode(nullptr),
      chunkyNodeSize(chunksize),
      countVariable(0) {} // added this line

MyChunkyNode::~MyChunkyNode() {
  delete[] itemsArray;
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
    if (index < 0 || index >= countVariable) {
        throw std::out_of_range("Index out of range");
    }

    // Shift elements to fill the gap of the removed element
    for (int i = index; i < countVariable - 1; ++i) {
        itemsArray[i] = itemsArray[i + 1];
    }

    // Decrease the countVariable by one
    --countVariable;
}


void MyChunkyNode::decrementCount() {
    if (countVariable > 0) // assuming countVariable is the variable tracking the number of items
        countVariable--;
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

void MyChunkyNode::split() {
  int total_count = count();

  if (total_count > chunkyNodeSize) {
    int first_node_size = total_count / 2;
    int second_node_size = total_count - first_node_size;

    // If the total count is odd, the first node should hold one more item
    if (total_count % 2 != 0) {
      first_node_size++;
      second_node_size--;
    }

    // Create the new node
    MyChunkyNode* new_node = new MyChunkyNode(chunkyNodeSize);

    // Move items to the new node
    for (int i = 0; i < second_node_size; i++) {
      new_node->itemsArray[i] = itemsArray[first_node_size + i];
      itemsArray[first_node_size + i].clear();
    }

    // Update counts
    countVariable = first_node_size;
    new_node->countVariable = second_node_size;

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
  // Only merge if the next node exists and the total number of items in this node and the next node is less than or equal to chunkyNodeSize
  if ((nextNode && (count() + nextNode->count()) <= chunkyNodeSize)) {
    // Move items from the next node to this node
    for (int i = 0; i < nextNode->count(); i++) {
      itemsArray[count() + i] = nextNode->itemsArray[i];
    }

    // Adjust the count variables
    countVariable += nextNode->countVariable;

    // Hold the nextNode in a temp pointer
    MyChunkyNode* toDelete = nextNode;

    // Update the next pointer of this node and prev pointer of nextNode's next node
    nextNode = nextNode->nextNode;
    if (nextNode) {
      nextNode->prevNode = this;
    }

    delete toDelete;  // Delete the nextNode as it's now merged with this node
  }
}


