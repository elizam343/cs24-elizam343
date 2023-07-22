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

  // Split the node if needed
  splitNodeIfNeeded(NodeTail);

  // Merge nodes if possible
  if (NodeTail->next() && NodeTail->count() + NodeTail->next()->count() <= chunkyNodeSize / 2) {
    NodeTail->merge();
  }
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

  // Split the node if needed
  splitNodeIfNeeded(NodeTail);

  // Merge nodes if possible
  if (NodeTail->next() && NodeTail->count() + NodeTail->next()->count() <= chunkyNodeSize / 2) {
    NodeTail->merge();
  }
}

void MyChunkyList::splitNodeIfNeeded(MyChunkyNode* node) {
  int current_count = node->getCount();
  int chunkyNodeSize = node->getChunkSize(); // Use the getter to get chunk size

  // No need to split if the current_count is less than chunk size
  if (current_count < chunkyNodeSize)
    return;

  int new_chunksize = chunkyNodeSize / 2;
  if (chunkyNodeSize % 2 == 1) {
    new_chunksize += 1; // Add one more item to the first node for odd chunk size
  }

  MyChunkyNode* new_node = new MyChunkyNode(new_chunksize);

  int first_half = current_count / 2;
  int second_half = current_count - first_half;

  for (int i = 0; i < second_half; i++) {
    new_node->insertItem(i, node->items()[first_half + i]);
    node->items()[first_half + i].clear();
  }

  // Update counts for both nodes
  node->setChunkSize(first_half);
  new_node->setChunkSize(second_half);

  new_node->setNext(node->next());
  new_node->setPrev(node);
  if (node->next()) {
    node->next()->setPrev(new_node);
  }
  node->setNext(new_node);
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