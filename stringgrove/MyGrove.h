#ifndef MYGROVE_H
#define MYGROVE_H

struct Node {
    char* data;
    Node* left;
    Node* right;

    Node(const char* str);
    Node(Node* leftNode, Node* rightNode);
};

class MyGrove {
public:
    Node** nodes;
    int nodeCount;
    int nodeCapacity;

    MyGrove();
    ~MyGrove();

    void create(const char* str);
    void concat(int id1, int id2);
    void print(int id);
    MyGrove(const char* str);
};

#endif
