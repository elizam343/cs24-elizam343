#include "MyChunkyList.h"

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

void MyChunkyList::insert(int index, const std::string& item) {
  if (index < 0 || index > count()) {
    return;
  }

  if (!NodeHead) {
    // The list is empty, create the head node
    NodeHead = NodeTail = new MyChunkyNode(chunkyNodeSize);
    NodeHead->insert(0, item);
    return;
  }

  int current_count = count();
  if (index == 0 && current_count < chunkyNodeSize) {
    NodeHead->insert(0, item);
  } else if (index == current_count && current_count < chunkyNodeSize) {
    NodeTail->insert(NodeTail->count(), item);
  } else {
    // Find the node to insert the item
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

string& MyChunkyList::lookup(int index) {
  static string empty_string = "";

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
    return;
  }

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
  if (NodeHead && NodeHead->count() == 0) {
    MyChunkyNode* new_head = NodeHead->next();
    delete NodeHead;
    NodeHead = new_head;
    if (NodeHead) {
      NodeHead->setPrev(nullptr);
    }
  }

  // Check if the tail node is empty, if yes, remove it
  if (NodeTail && NodeTail->count() == 0) {
    MyChunkyNode* new_tail = NodeTail->prev();
    delete NodeTail;
    NodeTail = new_tail;
    if (NodeTail) {
      NodeTail->setNext(nullptr);
    }
  }
}

