#include "MyGrove.h"
#include <iostream>

MyGrove::MyGrove(const char* str) {
    create(str);
}

MyGrove::MyGrove() {
    nodes = new Node*[10];
    nodeCount = 0;
    nodeCapacity = 10;
}

MyGrove::~MyGrove() {
    for(int i = 0; i < nodeCount; i++) {
        delete[] nodes[i]->data;
        delete nodes[i];
    }
    delete[] nodes;
}

void MyGrove::create(const char* str) {
    if(nodeCount == nodeCapacity) {
        Node** newNodes = new Node*[nodeCapacity*2];
        for(int i = 0; i < nodeCount; i++) newNodes[i] = nodes[i];
        delete[] nodes;
        nodes = newNodes;
        nodeCapacity *= 2;
    }
    nodes[nodeCount++] = new Node(str);
}

void MyGrove::concat(const MyGrove* otherGrove) {
    int newSize = this->nodeCount + otherGrove->nodeCount;
    MyGrove::Node** newNodes = new MyGrove::Node*[newSize];

    // Copy nodes from the current grove
    for (int i = 0; i < this->nodeCount; ++i) {
        newNodes[i] = this->nodes[i];
    }

    // Copy nodes from the other grove
    for (int i = 0; i < otherGrove->nodeCount; ++i) {
        newNodes[this->nodeCount + i] = new Node(*(otherGrove->nodes[i])); // Assuming Node has a copy constructor.
    }

    delete[] this->nodes; // Free old memory
    this->nodes = newNodes; // Point to new memory
    this->nodeCount = newSize;
}





char MyGrove::charAt(int index) const {
    if (!this->node || index < 0 || index >= this->node->length) {
        throw std::out_of_range("Index out of range");
    }
    return charAtNode(this->node, index);
}




char MyGrove::charAtNode(const Node* node, int index) const {
    if(index < 0 || index >= node->length) {
        throw std::out_of_range("Index out of range");
    }
    if(node->left && index < node->left->length) {
        return charAtNode(node->left, index);
    }
    else if(node->right) {
        return charAtNode(node->right, index - (node->left ? node->left->length : 0));
    }
    else {
        return node->data[index];
    }
}



MyGrove::Node* MyGrove::substrNode(const Node* current, int start, int end) const {
    if (start >= end) {
        return nullptr; // base case
    }
    
    if (!current->left && !current->right) { // leaf node
        char* substring = new char[end - start + 1];
        std::copy(current->data + start, current->data + end, substring);
        substring[end - start] = '\0';
        return new Node(substring);
    } else {
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
}

int MyGrove::len() const {
    if (nodeCount <= 0) {
        throw std::out_of_range("No nodes available");
    }
    return nodes[nodeCount - 1]->length;
}





MyGrove* MyGrove::substr(int start, int end) const {
    if (start < 0 || end > len() || start >= end) {
        throw std::out_of_range("Index out of range");
    }
    
    MyGrove* newGrove = new MyGrove();
    newGrove->node = substrNode(node, start, end);
    return newGrove;
}



void MyGrove::print(int id) {
    if(id < 0 || id >= nodeCount) {
        std::cout << "Invalid node id" << std::endl;
        return;
    }
    printNode(nodes[id]);
    std::cout << std::endl;
}

void MyGrove::printNode(Node* node) {
    if(node->left) {
        printNode(node->left);
    }
    if(node->right) {
        printNode(node->right);
    }
    else {
        std::cout << node->data;
    }
}

MyGrove::Node::Node(const char* data) {
    int length = 0;
    while(data[length] != '\0') {
        length++;
    }
    this->data = new char[length + 1];
    for(int i = 0; i < length; i++) {
        this->data[i] = data[i];
    }
    this->data[length] = '\0';
    this->length = length;
    this->left = nullptr;
    this->right = nullptr;
}

MyGrove::Node::Node(Node* left, Node* right) {
    this->left = left;
    this->right = right;
    this->data = nullptr;
    this->length = left->length + right->length;
}

