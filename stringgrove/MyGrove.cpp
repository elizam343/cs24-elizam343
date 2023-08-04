#include "MyGrove.h"
#include <iostream>

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
    if(node->left) {
        if(index < node->left->length) {
            return charAtNode(node->left, index);
        }
        else {
            return charAtNode(node->right, index - node->left->length);
        }
    }
    else {
        return node->data[index];
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
