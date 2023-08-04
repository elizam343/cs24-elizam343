#include "MyGrove.h"
#include <stdexcept>
#include <cstring>

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
    if (node->left)
        deleteNodes(node->left);
    if (node->right)
        deleteNodes(node->right);
    delete node;
}

int MyGrove::len() const {
    return root->length;
}

Node* MyGrove::concatNodes(Node* node1, Node* node2) {
    Node* newNode = new Node;
    newNode->data = nullptr; // Join nodes do not hold data
    newNode->length = node1->length + node2->length;
    newNode->left = node1;
    newNode->right = node2;
    return newNode;
}

const MyGrove* MyGrove::concat(MyGrove* other) const {
    MyGrove* newGrove = new MyGrove("");
    newGrove->root = concatNodes(this->root, other->root);
    return newGrove;
}

char MyGrove::charAt(int index) const {
    if (index >= root->length || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = root;
    while (current->left || current->right) {
        if (current->left && index < current->left->length) {
            current = current->left;
        } else {
            index -= current->left ? current->left->length : 0;
            current = current->right;
        }
    }
    return current->data[index];
}

Node* MyGrove::substrNode(Node* node, int start, int end) {
    if (start > end || start < 0 || end > node->length) {
        throw std::out_of_range("Invalid start or end index for substring");
    }

    if (!node->left && !node->right) { // If the node is a leaf
        Node* newNode = new Node;
        newNode->data = node->data + start; // Set the data pointer to the start of the substring
        newNode->length = end - start;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    } else {
        if (end <= node->left->length) {
            return substrNode(node->left, start, end);
        } else if (start >= node->left->length) {
            return substrNode(node->right, start - node->left->length, end - node->left->length);
        } else {
            Node* newNode = new Node;
            newNode->data = nullptr;
            newNode->length = end - start;
            newNode->left = substrNode(node->left, start, node->left->length);
            newNode->right = substrNode(node->right, 0, end - node->left->length);
            return newNode;
        }
    }
}

const MyGrove* MyGrove::substr(int start, int end) const {
    MyGrove* newGrove = new MyGrove("");
    newGrove->root = substrNode(root, start, end);
    return newGrove;
}
