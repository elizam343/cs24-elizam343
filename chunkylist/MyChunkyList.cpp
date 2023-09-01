
#include "MyChunkyList.h"
#include <stdexcept>

MyChunkyList::MyChunkyList(int chunksize)
    : NodeHead(nullptr), NodeTail(nullptr), chunkyNodeSize(chunksize) {}

MyChunkyList::~MyChunkyList() {
  MyChunkyNode* current = NodeHead;
  while (current) {
    MyChunkyNode* next = current->next();
    delete current;
    current = next;
  }
}

int MyChunkyList::count() const {
  int total_count = 0;
  MyChunkyNode* current = NodeHead;
  while (current) {
    total_count += current->count();
    current = current->next();
  }
  return total_count;
}

void MyChunkyList::splitAndMerge() {
  // First, merge nodes as necessary
  MyChunkyNode* current = head();
  while (current) {
    current->merge();
    current = current->next();
  }

  // Then, split nodes as necessary
  current = head();
  while (current) {
    current->split();
    current = current->next();
  }
}

void MyChunkyList::insert(int index, const std::string& item) {
    if (index < 0 || index > count()) {
        throw std::out_of_range("Index out of range");
    }

    // Create a new node if list is empty
    if (!NodeHead) {
        NodeHead = NodeTail = new MyChunkyNode(chunkyNodeSize);
        NodeHead->insert(0, item);
        return;
    }

    // Find the node to insert into
    MyChunkyNode* current = NodeHead;
    int current_index = 0;
    while (current) {
        int nodeCount = current->count();

        // If this is the right node for insertion
        if (index <= current_index + nodeCount) {
            current->insert(index - current_index, item);

            // If the node is overfull after insertion, split it
            if (current->count() > chunkyNodeSize) {
                MyChunkyNode* newNode = current->split();  // This should return the new node
                
                // Link the new node to the list
                newNode->setNext(current->next());
                newNode->setPrev(current);
                if (current->next()) {
                    current->next()->setPrev(newNode);
                } else {
                    NodeTail = newNode;  // If current was the tail, update tail
                }
                current->setNext(newNode);
            }
            return;
        }
        
        current_index += nodeCount;
        current = current->next();
    }
}


std::string& MyChunkyList::lookup(int index) {
  if (index < 0 || index >= count()) {
    throw std::out_of_range("Index out of range");
  }

  int node_index = 0;
  MyChunkyNode* current = NodeHead;
  while (current) {
    int node_count = current->count();
    if (index >= node_index && index < node_index + node_count) {
      return current->items()[index - node_index];
    }
    node_index += node_count;
    current = current->next();
  }

  throw std::out_of_range("Index out of range");
}

void MyChunkyList::remove(int index) {
  if (index < 0 || index >= count()) {
    throw std::out_of_range("Index out of range");
  }

  MyChunkyNode* current = NodeHead;
  int current_index = 0;

  while (current) {
    if (index < current_index + current->count()) {
      current->remove(index - current_index); // This function should adjust countVariable

      // If the current node is empty, remove it
      if (current->count() == 0) {
        MyChunkyNode* prevNode = current->prev();
        MyChunkyNode* nextNode = current->next();

        if (prevNode) {
          prevNode->setNext(nextNode);
        } else { // the current node was the head
          NodeHead = nextNode;
        }

        if (nextNode) {
          nextNode->setPrev(prevNode);
        } else { // the current node was the tail
          NodeTail = prevNode;
        }

        delete current;
        current = nullptr;

        // If prevNode and nextNode exist and can be merged, do so
        if (prevNode && nextNode && prevNode->count() + nextNode->count() <= chunkyNodeSize) {
          prevNode->merge(); // This function should handle merging and deleting nodes
          if (nextNode->next()) { // the nextNode was not the tail
            nextNode->next()->setPrev(prevNode);
          }
          prevNode->setNext(nextNode->next());
        }
      }

      // If the current node is not empty but can be merged with previous node, merge them
      else if (current->prev() && current->prev()->count() + current->count() <= chunkyNodeSize) {
        MyChunkyNode* prevNode = current->prev();
        prevNode->merge(); // This function should handle merging and deleting nodes
        current = prevNode; // as current might have been deleted, step back
      }
      break;
    }
    current_index += current->count();
    current = current->next();
  }
}




MyChunkyNode* MyChunkyList::head() const {
  return NodeHead;
}

MyChunkyNode* MyChunkyList::tail() const {
  return NodeTail;
}