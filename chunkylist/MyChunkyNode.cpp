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
    if (index < 0 || index > countVariable) {
        throw std::out_of_range("Index out of range");
    }

    if (countVariable < chunkyNodeSize) {
        // Shift elements to the right of the insert location to make room for the new element
        for (int i = countVariable; i > index; --i) {
            itemsArray[i] = itemsArray[i - 1];
        }

        // Insert the new element and increase the countVariable by one
        itemsArray[index] = item;
        ++countVariable;
    } else {
        // The node is full, so we need to split it
        MyChunkyNode* newNode = new MyChunkyNode(chunkyNodeSize);
        
        // Move half of the elements to the new node
        int mid = chunkyNodeSize / 2;
        for (int i = mid; i < chunkyNodeSize; ++i) {
            newNode->append(itemsArray[i]);
        }

        // Remove moved elements from original node
        countVariable = mid;

        // Insert the new element
        if (index <= mid) {
            this->insert(index, item);
        } else {
            newNode->insert(index - mid, item);
        }

        // Update next and previous pointers
        newNode->nextNode = this->nextNode;
        if (newNode->nextNode != nullptr) {
            newNode->nextNode->prevNode = newNode;
        }
        this->nextNode = newNode;
        newNode->prevNode = this;
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

    // Check if this node is less than half full and the next node is not empty
    if (countVariable < chunkyNodeSize / 2 && nextNode != nullptr && nextNode->countVariable > 0) {
        // Merge this node with the next node
        for (int i = 0; i < nextNode->countVariable; ++i) {
            this->append(nextNode->itemsArray[i]);
        }

        // Update the next and previous pointers
        MyChunkyNode* tempNode = nextNode;
        nextNode = nextNode->nextNode;
        if (nextNode != nullptr) {
            nextNode->prevNode = this;
        }

        // Delete the merged node
        delete tempNode;
    }
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


