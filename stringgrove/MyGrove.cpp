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

void MyGrove::concat(int id1, int id2) {
    if(id1 < 0 || id1 >= nodeCount || id2 < 0 || id2 >= nodeCount) {
        std::cout << "Invalid node id" << std::endl;
        return;
    }
    nodes[nodeCount++] = new Node(nodes[id1], nodes[id2]);
}

char MyGrove::charAt(int id, int index) {
    if(id < 0 || id >= nodeCount) {
        throw std::out_of_range("Invalid node id");
    }
    return charAtNode(nodes[id], index);
}

char MyGrove::charAtNode(Node* node, int index) {
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


MyGrove::Node* MyGrove::substrNode(Node* node, int start, int end) {
    if(start < 0 || end >= node->length) {
        throw std::out_of_range("Index out of range");
    }
    if(node->left) {
        // Recurse into left and right child nodes
        Node* left = (start < node->left->length) ? substrNode(node->left, start, std::min(end, node->left->length)) : nullptr;
        Node* right = (end >= node->left->length) ? substrNode(node->right, std::max(0, start - node->left->length), end - node->left->length) : nullptr;
        return new Node(left, right);
    }
    else {
        // If substring is supposed to be empty, just return a new node with an empty string
        if (end - start <= 0) {
            return new Node("");
        }

        // Allocate a new C-string to hold the substring
        char* substring = new char[end - start + 2];

        // Now copy the data from node->data into substring
        for(int i = start; i <= end; i++) {
            if (node->data == nullptr || i < 0 || i >= node->length) {
                throw std::runtime_error("Invalid data or index");
            }
            substring[i - start] = node->data[i];
        }
        substring[end - start + 1] = '\0';  // Null terminate the C-string
        return new Node(substring);
    }
}


MyGrove* MyGrove::substr(int id, int start, int end) {
    if(id < 0 || id >= nodeCount) {
        throw std::out_of_range("Invalid node id");
    }
    MyGrove* newGrove = new MyGrove();
    newGrove->create("");
    newGrove->nodes[0] = substrNode(nodes[id], start, end);
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
