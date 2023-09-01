#include "MyGrove.h"
#include <iostream>
#include <cassert>

void test_create() {
    MyGrove grove;
    grove.create("hello");
    grove.create("world");
    // Check if nodeCount is as expected
    assert(grove.getNodeCount() == 2);
    // You can add more tests based on your implementation
}

void test_concat() {
    MyGrove grove1;
    grove1.create("Hello");
    grove1.create("World");

    MyGrove grove2;
    grove2.create("!");

    MyGrove* concatenatedGrove = grove1.concat(&grove2);

    assert(concatenatedGrove->getNodeCount() == 3); // Assuming concat creates a new node

    // Cleanup
    delete concatenatedGrove;
}


void test_substr() {
    MyGrove grove;
    grove.create("helloworld");
    MyGrove* subGrove = grove.substr(0, 5);
    // Validate if subGrove contains the correct substring
    // Again, this might require methods to expose internal data
    // Add more tests as necessary
    delete subGrove;
}

int main() {
    test_create();
    test_concat();
    test_substr();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
