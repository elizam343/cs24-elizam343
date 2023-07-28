#include "MyStack.h"
#include <stdexcept>

MyStack::MyStack() {}

void MyStack::clear() {
    data.clear();
}

bool MyStack::is_empty() const {
    return data.empty();
}

void MyStack::push(double item) {
    data.push_back(item);
}

double MyStack::pop() {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty");
    }
    double top_value = data.back();
    data.pop_back();
    return top_value;
}

double MyStack::top() const {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty");
    }
    return data.back();
}