#ifndef MYGROVE_H
#define MYGROVE_H

class Node {
public:
    Node(const char* str);
    Node(Node* leftNode, Node* rightNode);
    char* data;
    Node* left;
    Node* right;
};

class MyGrove {
private:
    Node** nodes;
    int nodeCount;
    int nodeCapacity;
    void printNode(Node* node);
public:
    MyGrove(const char* str);
    MyGrove();
    ~MyGrove();
    void create(const char* str);
    void concat(int id1, int id2);
    void print(int id);
};

#endif
