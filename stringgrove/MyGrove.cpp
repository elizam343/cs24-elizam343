#include "MyGrove.h"
#include <cstring> // For strlen
#include <stdexcept> // For std::out_of_range

MyGrove::MyGrove(const char* str) {
    root = new Node;
    root->data = str;
    root->length = strlen(str);
    root->left = nullptr;
    root->right = nullptr;
}

MyGrove::~MyGrove() {
    deleteNodes(root);
}

void MyGrove::deleteNodes(Node* node) {
    if (node) {
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    }
}

int MyGrove::len() const {
    return root->length;
}

MyGrove::Node* MyGrove::concatNodes(Node* node1, Node* node2) const {
    // TODO: Implement the recursive concatenation logic here.
}

const MyGrove* MyGrove::concat(MyGrove* other) const {
    // TODO: Implement the efficient concatenation logic here.
}

char MyGrove::charAt(int index) const {
    // TODO: Implement the function to return the character at the given index.
}

MyGrove::Node* MyGrove::substrNode(Node* node, int start, int end) const {
    // TODO: Implement the recursive substring logic here.
}

const MyGrove* MyGrove::substr(int start, int end) const {
    // TODO: Implement the efficient substring logic here.
}
