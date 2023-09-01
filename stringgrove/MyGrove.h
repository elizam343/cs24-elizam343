#ifndef MYGROVE_H
#define MYGROVE_H

class MyGrove { 
public:
    static constexpr int INITIAL_CAPACITY = 10;
    class Node {
    public:
        char* data;
        Node* left;
        Node* right;
        int length;

        Node(Node* leftNode, Node* rightNode);
    };

    MyGrove();
    MyGrove(const char* str);
    ~MyGrove();

    void create(const char* str);
    MyGrove* concat(const MyGrove* otherGrove) const;
    void print(int id);
    void printNode(Node* node);
    char charAt(int index) const;
    MyGrove* substr(int start, int end) const;
    int len() const;
    int getNodeCount() const {
        return nodeCount;
    }

private:
    Node** nodes;
    Node* node; 
    int nodeCount;
    int nodeCapacity;

    char charAtNode(const Node* node, int index) const;
    Node* substrNode(const Node* node, int start, int end) const;

};


#endif
