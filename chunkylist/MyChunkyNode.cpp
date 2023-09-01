
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

    // If inserting at the start and the current node is the first node and it's full
    if (index == 0 && prevNode == nullptr && countVariable == chunkyNodeSize) {
        MyChunkyNode* newNode = new MyChunkyNode(chunkyNodeSize);
        newNode->append(item);
        newNode->setNext(this);
        this->setPrev(newNode);
        return;
    }

    // If inserting at the end and the current node is the last node and it's full
    if (index == countVariable && nextNode == nullptr && countVariable == chunkyNodeSize) {
        MyChunkyNode* newNode = new MyChunkyNode(chunkyNodeSize);
        newNode->append(item);
        newNode->setPrev(this);
        this->setNext(newNode);
        return;
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
        
        // Calculate how many items should remain in the current node after the split
        int remainingInCurrent = (countVariable + 1) / 2; 
        if (index < remainingInCurrent) {
            // Move items starting from the index of insert to the new node
            for (int i = index; i < countVariable; ++i) {
                newNode->append(itemsArray[i]);
            }
            // Adjust count for the current node
            countVariable = index;
            // Insert the new item
            this->insert(index, item);
        } else {
            // Move items starting from one position after where we want to insert to the new node
            for (int i = remainingInCurrent; i < countVariable; ++i) {
                newNode->append(itemsArray[i]);
            }
            // Adjust count for the current node
            countVariable = remainingInCurrent;
            // Insert the new item in the new node
            newNode->insert(index - remainingInCurrent, item);
        }

        // Adjust the next pointers
        newNode->setNext(this->next());
        if (newNode->next() != nullptr) {
            newNode->next()->setPrev(newNode);
        }
        this->setNext(newNode);
        newNode->setPrev(this);
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
        for (int i = countVariable, j = 0; i < chunkyNodeSize && j < nextNode->countVariable; ++i, ++j) {
            this->itemsArray[i] = nextNode->itemsArray[j];
        }
        int mergedCount = nextNode->countVariable;
        this->countVariable += mergedCount;

        // Shift elements in the next node
        for (int i = 0, j = mergedCount; j < nextNode->countVariable; ++i, ++j) {
            nextNode->itemsArray[i] = nextNode->itemsArray[j];
        }
        nextNode->countVariable -= mergedCount;

        // Check if the next node is empty
        if (nextNode->countVariable == 0) {
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
        int first_node_size;
        int second_node_size;

        // Explicitly handle even chunks
        if (total_count % 2 == 0) {
            first_node_size = total_count / 2;
            second_node_size = total_count / 2;
        } else {
            first_node_size = (total_count / 2) + 1;
            second_node_size = total_count - first_node_size;
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
    // Check if next node exists and if merging doesn't exceed the maximum chunk size
    if (nextNode && (countVariable + nextNode->countVariable) <= chunkyNodeSize) {

        // Move items from the next node to this node
        for (int i = 0; i < nextNode->countVariable; i++) {
            if (countVariable + i >= chunkyNodeSize) {
                throw std::runtime_error("Attempting to write past the end of itemsArray");
            }
            itemsArray[countVariable + i] = nextNode->itemsArray[i];
        }

        // Update item count for current node
        countVariable += nextNode->countVariable;

        // Update the linked list pointers
        MyChunkyNode* toDelete = nextNode;  // Temporary pointer for later deletion
        nextNode = nextNode->nextNode;      
        if (nextNode) {
            nextNode->prevNode = this;
        }

        // Delete the merged node
        delete toDelete;
    }
}




