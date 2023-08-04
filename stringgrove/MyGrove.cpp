#include "MyGrove.h"
#include <iostream>

Node::Node(const char* str) {
    int len = 0;
    while(str[len] != '\0') len++;  // count length

    data = new char[len+1];
    for(int i = 0; i <= len; i++) data[i] = str[i];  // copy string
    left = right = nullptr;
}

Node::Node(Node* leftNode, Node* rightNode) {
    // Do not explicitly concatenate data here.
    // Just set left and right pointers
    left = leftNode;
    right = rightNode;
}

MyGrove::MyGrove(const char* str) {
    create(str);  // Call the create method to add a new node with the string
}

MyGrove::MyGrove() {
    nodes = new Node*[10];  // start with capacity 10
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
    if(nodeCount == nodeCapacity) {  // resize if necessary
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

void MyGrove::print(int id) {
    if(id < 0 || id >= nodeCount) {
        std::cout << "Invalid node id" << std::endl;
        return;
    }
    
    // Modify print method to handle joint nodes
    printNode(nodes[id]);
    std::cout << std::endl;
}

void MyGrove::printNode(Node* node) {
    if(node->left != nullptr)
        printNode(node->left);
    
    if(node->right != nullptr)
        printNode(node->right);
        
    if(node->left == nullptr && node->right == nullptr)
        std::cout << node->data;
}
