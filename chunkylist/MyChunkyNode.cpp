#include "MyChunkyNode.h"

MyChunkyNode::MyChunkyNode(int chunksize)
    : itemsArray(new std::string[chunksize]),
      prevNode(nullptr),
      nextNode(nullptr),
      chunkyNodeSize(chunksize) {
    // Initialize the itemsArray to empty strings
    for (int i = 0; i < chunkyNodeSize; i++) {
        itemsArray[i] = "";
    }
}

MyChunkyNode::~MyChunkyNode() {
    // Traverse the list of nodes and delete each node
    MyChunkyNode* current = this;
    while (current) {
        MyChunkyNode* next = current->nextNode;
        delete[] current->itemsArray;
        current->prevNode = nullptr; // Set prevNode to nullptr to avoid dangling pointers
        current->nextNode = nullptr; // Set nextNode to nullptr to avoid dangling pointers
        delete current;
        current = next;
    }
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

    if (current_count < chunkyNodeSize) {
        // There is space in the current node, shift elements and insert
        for (int i = current_count; i > index; i--) {
            itemsArray[i] = itemsArray[i - 1];
        }
        itemsArray[index] = item;
    } else {
        // The current node is full, split it
        splitNode();
        insert(index, item); // Re-insert the item after splitting
    }
}

void MyChunkyNode::remove(int index) {
    int current_count = count();

    if (current_count > 0) {
        // Shift elements to remove the item
        for (int i = index; i < current_count - 1; i++) {
            itemsArray[i] = itemsArray[i + 1];
        }
        itemsArray[current_count - 1].clear();

        // Check if the node can be merged with the next node
        mergeNext();
    }
}

void MyChunkyNode::splitNode() {
    int new_chunksize = chunkyNodeSize / 2;
    MyChunkyNode* new_node = new MyChunkyNode(new_chunksize);

    // Move half of the items to the new node
    for (int i = 0; i < new_chunksize; i++) {
        new_node->itemsArray[i] = itemsArray[chunkyNodeSize - new_chunksize + i];
        itemsArray[chunkyNodeSize - new_chunksize + i].clear();
    }

    // Adjust the pointers
    new_node->setNext(nextNode);
    new_node->setPrev(this);
    if (nextNode) {
        nextNode->setPrev(new_node);
    }
    setNext(new_node);
}

void MyChunkyNode::mergeNext() {
    if (nextNode) {
        int total_count = count() + nextNode->count();

        // Check if the next node can be merged
        if (total_count <= chunkyNodeSize / 2) {
            // Move items from the next node to the current node
            for (int i = 0; i < nextNode->count(); i++) {
                itemsArray[count() + i] = nextNode->items()[i];
            }

            // Adjust pointers and delete the next node
            MyChunkyNode* next_next_node = nextNode->next();
            if (next_next_node) {
                next_next_node->setPrev(this);
            }
            setNext(next_next_node);
            delete nextNode;
        }
    }
}
