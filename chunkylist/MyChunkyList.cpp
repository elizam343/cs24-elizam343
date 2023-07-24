
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

  // If inserting at the start of the list and the head node is full, create a new head node
  if (index == 0 && NodeHead->count() == chunkyNodeSize) {
    MyChunkyNode* new_node = new MyChunkyNode(chunkyNodeSize);
    new_node->setNext(NodeHead);
    NodeHead->setPrev(new_node);
    NodeHead = new_node;
    NodeHead->insert(0, item);
    return;
  }

  // If inserting at the end of the list and the tail node is full, create a new tail node
  if (index == count() && NodeTail->count() == chunkyNodeSize) {
    MyChunkyNode* new_node = new MyChunkyNode(chunkyNodeSize);
    new_node->setPrev(NodeTail);
    NodeTail->setNext(new_node);
    NodeTail = new_node;
    NodeTail->insert(0, item);
    return;
  }

  // Find the node to insert into and insert the item
  MyChunkyNode* current = NodeHead;
  int current_index = 0;
  while (current) {
    if (index <= current_index + current->count()) {
      if (current->count() < chunkyNodeSize) {
        // Insert into this node if there's room
        current->insert(index - current_index, item);
        return;
      } else {
        // If the node is full, split it before inserting
        current->split();
        current->insert(index - current_index, item);
        return;
      }
    }
    current_index += current->count();
    current = current->next();
  }
  if (current) {
    current->merge();
    if (current->next()) {
      current->next()->merge();
    }
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
            current->remove(index - current_index);
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