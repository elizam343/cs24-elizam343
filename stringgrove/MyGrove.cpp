#include "MyGrove.h"
#include <iostream>
#include <cstring>

MyGrove::MyGrove(const char* str) {
    create(str);
}

MyGrove::MyGrove() {
    nodes = new Node*[INITIAL_CAPACITY];
    nodeCount = 0;
    nodeCapacity = INITIAL_CAPACITY;
    nodes = new Node*[nodeCapacity];
}


MyGrove::~MyGrove() {
    for(int i = 0; i < nodeCount; i++) {
        delete[] nodes[i]->data;
        delete nodes[i];
    }
    delete[] nodes;
}



MyGrove::Node::~Node() {
    delete[] data;
}


MyGrove::Node::Node(const char* data) {
    length = strlen(data);
    this->data = new char[length + 1];
    strcpy(this->data, data);
    left = nullptr;
    right = nullptr;
}

MyGrove::Node::Node(Node* leftNode, Node* rightNode) {
    left = leftNode;
    right = rightNode;
    
    // Assuming you want to concatenate the data from both nodes:
    int leftLength = (leftNode) ? strlen(leftNode->data) : 0;
    int rightLength = (rightNode) ? strlen(rightNode->data) : 0;
    
    data = new char[leftLength + rightLength + 1]; // +1 for null terminator
    if(leftNode) strcpy(data, leftNode->data);
    if(rightNode) strcpy(data + leftLength, rightNode->data);
    
    // Set the length of the new node
    length = leftLength + rightLength;
}


void MyGrove::create(const char* str) {
    // Check and expand the nodes array if necessary
    if (nodeCount == nodeCapacity) {
        nodeCapacity *= 2;
        Node** newNodes = new Node*[nodeCapacity];
        for (int i = 0; i < nodeCount; i++) {
            newNodes[i] = nodes[i];
        }
        delete[] nodes;
        nodes = newNodes;
    }
    
    // Add the new Node
    nodes[nodeCount++] = new Node(str);
}




MyGrove* MyGrove::concat(const MyGrove* otherGrove) const {
    MyGrove* newGrove = new MyGrove();
    int newSize = this->nodeCount + otherGrove->nodeCount;
    newGrove->nodes = new MyGrove::Node*[newSize];

    // Deep copy nodes from the current grove
    for (int i = 0; i < this->nodeCount; ++i) {
        newGrove->nodes[i] = new Node(*(this->nodes[i]));
    }

    // Deep copy nodes from the other grove
    for (int i = 0; i < otherGrove->nodeCount; ++i) {
        newGrove->nodes[this->nodeCount + i] = new Node(*(otherGrove->nodes[i]));
    }

    newGrove->nodeCount = newSize;
    return newGrove;
}

char MyGrove::charAt(int index) const {
    if (index < 0 || index >= len()) {  
        throw std::out_of_range("Index out of range");
    }

    int accumulatedLength = 0;
    for (int i = 0; i < nodeCount; ++i) {
        if (index < accumulatedLength + nodes[i]->length) {
            return charAtNode(nodes[i], index - accumulatedLength);
        }
        accumulatedLength += nodes[i]->length;
    }

    throw std::logic_error("charAt reached an unexpected state");
}




char MyGrove::charAtNode(const Node* node, int index) const {
    if(index < 0 || index >= node->length) {
        throw std::out_of_range("Index out of range");
    }
    if(node->left && index < node->left->length) {
        return charAtNode(node->left, index);
    } else if(node->right) {
        return charAtNode(node->right, index - (node->left ? node->left->length : 0));
    } else {
        return node->data[index];
    }
}

MyGrove::Node* MyGrove::substrNode(const Node* current, int start, int end) const {
    if (start >= end || !current) return nullptr;
    
    if (!current->left && !current->right) { // leaf node
        char* substring = new char[end - start + 1];
        strncpy(substring, current->data + start, end - start);
        substring[end - start] = '\0';
        return new Node(substring);
    } 

    int leftLength = current->left ? current->left->length : 0;

    if (end <= leftLength) {
        return substrNode(current->left, start, end);
    } else if (start >= leftLength) {
        return substrNode(current->right, start - leftLength, end - leftLength);
    } else {
        Node* leftSubstr = substrNode(current->left, start, leftLength);
        Node* rightSubstr = substrNode(current->right, 0, end - leftLength);
        return new Node(leftSubstr, rightSubstr);
    }
}


int MyGrove::len() const {
    int totalLength = 0;
    for (int i = 0; i < nodeCount; ++i) {
        totalLength += nodes[i]->length;
    }
    return totalLength;
}


MyGrove* MyGrove::substr(int start, int end) const {
    if (start < 0 || end > len() || start >= end) {
        throw std::out_of_range("Index out of range");
    }
    
    MyGrove* newGrove = new MyGrove();

    // If there's no node, return an empty grove
    if(nodeCount <= 0) {
        return newGrove;
    }

    // Create a new node using the substring from the last node in nodes array
    Node* newSubstrNode = substrNode(nodes[nodeCount-1], start, end);
    if(newSubstrNode) {
        newGrove->create(newSubstrNode->data);
        delete newSubstrNode;  // Be careful about memory leaks!
    }

    return newGrove;
}


void MyGrove::print() const {
    for (int i = 0; i < nodeCount; ++i) {
        if(nodes[i]->data) std::cout << nodes[i]->data;
    }
    std::cout << std::endl;
}


std::string MyGrove::toString() const {
    std::string result;
    for (int i = 0; i < nodeCount; ++i) {
        result += nodes[i]->asString();
    }
    return result;
}



std::string MyGrove::Node::asString() const {
    // I don't know the exact structure of your Node class, so this is a simple placeholder.
    // You'll need to adjust this based on how your Node class is structured.
    std::string result;
    if (this->left) result += this->left->asString();
    // Assuming you have some 'data' member in the Node class.
    result += this->data;
    if (this->right) result += this->right->asString();
    return result;
}


MyGrove::Node* MyGrove::createNode(const char* data) const {
    Node* newNode = new Node(data);
    return newNode;
}

MyGrove::Node* MyGrove::concatNodes(Node* leftNode, Node* rightNode) const {
    Node* newNode = new Node(leftNode, rightNode);
    return newNode;
}

MyGrove::Node* MyGrove::copyNode(const Node* node) const {
    if (!node) {
        return nullptr;
    }
    Node* newNode = new Node(node->data);
    newNode->left = copyNode(node->left);
    newNode->right = copyNode(node->right);
    newNode->length = node->length;
    return newNode;
}

