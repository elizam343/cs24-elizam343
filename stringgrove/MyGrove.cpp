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
    int len1 = 0;
    while(leftNode->data[len1] != '\0') len1++;  // count lengths
    int len2 = 0;
    while(rightNode->data[len2] != '\0') len2++;

    data = new char[len1+len2+1];
    for(int i = 0; i < len1; i++) data[i] = leftNode->data[i];  // copy left node data
    for(int i = 0; i < len2; i++) data[i+len1] = rightNode->data[i];  // copy right node data
    data[len1+len2] = '\0';  // null terminate
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
    std::cout << "Node " << id << ": " << nodes[id]->data << std::endl;
}
