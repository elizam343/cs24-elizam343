#ifndef MYGROVE_H
#define MYGROVE_H

class MyGrove {
public:
    class Node {
    public:
        char* data;
        Node* left;
        Node* right;
        int length;

        Node(const char* str);
        Node(Node* leftNode, Node* rightNode);
    };

    MyGrove();
    MyGrove(const char* str);
    ~MyGrove();

    void create(const char* str);
    void concat(int id1, int id2);
    void print(int id);
    void printNode(Node* node);
    char charAt(int index);
    MyGrove* substr(int start, int end);
    int len() const;

private:
    Node** nodes;
    int nodeCount;
    int nodeCapacity;

    char charAtNode(Node* node, int index);
    Node* substrNode(Node* node, int start, int end);
};


#endif
