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
  MyChunkyNode* current = head();
  while (current) {
    current->split();
    current = current->next();
  }

  current = head();
  while (current) {
    current->merge();
    current = current->next();
  }
}

// ...

void MyChunkyList::insert(int index, const std::string& item) {
  if (index < 0 || index > count()) {
    throw std::out_of_range("Index out of range");
  }

  // Check if the list is empty and create the first node
  if (!NodeHead) {
    NodeHead = NodeTail = new MyChunkyNode(chunkyNodeSize);
    NodeHead->insert(0, item);
    return;
  }

  // Check if there's room in the tail node to insert the item
  if (NodeTail->count() < chunkyNodeSize) {
    NodeTail->insert(NodeTail->count(), item);
  } else {
    // Check if there's room in the head node to insert the item
    if (NodeHead->count() < chunkyNodeSize) {
      NodeHead->insert(0, item);
    } else {
      // Find the node to insert the item
      MyChunkyNode* current = NodeHead;
      int node_index = 0;
      while (current) {
        int node_count = current->count();
        if (index >= node_index && index <= node_index + node_count) {
          // Insert the item into the current node
          current->insert(index - node_index, item);
          break;
        }
        node_index += node_count;
        current = current->next();
      }
    }
  }

  // Split and merge nodes as needed
  splitAndMerge();
}

void MyChunkyList::remove(int index) {
  if (index < 0 || index >= count()) {
    throw std::out_of_range("Index out of range");
  }

  // Find the node to remove the item
  int node_index = 0;
  MyChunkyNode* current = NodeHead;
  while (current) {
    int node_count = current->count();
    if (index >= node_index && index < node_index + node_count) {
      // Remove the item from the current node
      current->remove(index - node_index);
      break;
    }
    node_index += node_count;
    current = current->next();
  }

  // Check if the head node is empty, if yes, remove it
  if (NodeHead->count() == 0) {
    MyChunkyNode* new_head = NodeHead->next();
    delete NodeHead;
    NodeHead = new_head;
    if (NodeHead) {
      NodeHead->setPrev(nullptr);
    } else {
      NodeTail = nullptr;
    }
  }

  // Check if the tail node is empty, if yes, remove it
  if (NodeTail->count() == 0) {
    MyChunkyNode* new_tail = NodeTail->prev();
    delete NodeTail;
    NodeTail = new_tail;
    if (NodeTail) {
      NodeTail->setNext(nullptr);
    } else {
      NodeHead = nullptr;
    }
  }

  // Split and merge nodes as needed
  splitAndMerge();
}




std::string& MyChunkyList::lookup(int index) {
  static std::string empty_string = "";

  if (index < 0 || index >= count()) {
    return empty_string;
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

  return empty_string;
}


MyChunkyNode* MyChunkyList::head() const {
  return NodeHead;
}

MyChunkyNode* MyChunkyList::tail() const {
  return NodeTail;
}