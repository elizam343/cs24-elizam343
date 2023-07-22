
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


void MyChunkyList::insert(int index, const std::string& item) {
  if (index < 0 || index > count()) {
    throw std::out_of_range("Index out of range");
  }

  if (index == 0) {
    // Inserting at the head
    if (NodeHead->count() < chunkyNodeSize) {
      // If the head node has space, insert the item in the head node
      NodeHead->insert(0, item);
    } else {
      // If the head node is full, create a new node and make it the new head
      MyChunkyNode* new_head = new MyChunkyNode(chunkyNodeSize);
      new_head->insert(0, item);
      new_head->setNext(NodeHead);
      NodeHead->setPrev(new_head);
      NodeHead = new_head;
    }
  } else if (index == count()) {
    // Inserting at the tail
    if (NodeTail->count() < chunkyNodeSize) {
      // If the tail node has space, insert the item in the tail node
      NodeTail->insert(NodeTail->count(), item);
    } else {
      // If the tail node is full, create a new node and make it the new tail
      MyChunkyNode* new_tail = new MyChunkyNode(chunkyNodeSize);
      new_tail->insert(0, item);
      new_tail->setPrev(NodeTail);
      NodeTail->setNext(new_tail);
      NodeTail = new_tail;
    }
  } else {
    int current_count = count();
    if (index == 0 && current_count < chunkyNodeSize) {
      NodeHead->insert(0, item);
    } else if (index == current_count && current_count < chunkyNodeSize) {
      NodeTail->insert(NodeTail->count(), item);
    } else {
      int node_index = 0;
      MyChunkyNode* current = NodeHead;
      while (current) {
        int node_count = current->count();
        if (index >= node_index && index <= node_index + node_count) {
          current->insert(index - node_index, item);
          break;
        }
        node_index += node_count;
        current = current->next();
      }
    }
  }
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

void MyChunkyList::remove(int index) {
  if (index < 0 || index >= count()) {
    throw std::out_of_range("Index out of range");
  }

  if (NodeHead && NodeHead->count() <= chunkyNodeSize / 2 && NodeHead->next()) {
    NodeHead->merge();
  }
  splitAndMerge();

  int node_index = 0;
  MyChunkyNode* current = NodeHead;
  while (current) {
    int node_count = current->count();
    if (index >= node_index && index < node_index + node_count) {
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
}

MyChunkyNode* MyChunkyList::head() const {
  return NodeHead;
}

MyChunkyNode* MyChunkyList::tail() const {
  return NodeTail;
}



  