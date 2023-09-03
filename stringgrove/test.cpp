#include <iostream>
#include "MyGrove.h"

int main() {
    // Test creating a simple grove and accessing characters
    MyGrove grove1("Hello");
    grove1.print();  // Expected: Hello
    std::cout << "Length of grove1: " << grove1.len() << std::endl;  // Expected: 5

    try {
        char ch = grove1.charAt(1);
        std::cout << "Character at index 1 of grove1: " << ch << std::endl;  // Expected: e
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        MyGrove* subGrove = grove1.substr(1, 4); // Should extract "ell"
        subGrove->print();  // Expected: ell
        delete subGrove;
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test concatenation
    MyGrove grove2(" World");
    MyGrove* concatenated = grove1.concat(&grove2);
    concatenated->print();  // Expected: Hello World
    delete concatenated;

    // Test edge cases
    MyGrove emptyGrove("");
    MyGrove* substrGrove = grove1.substr(1, 10);  // This should be out of range
    substrGrove->print();  // This should not be reached
    delete substrGrove;

    MyGrove* emptyConcat = grove1.concat(&emptyGrove);  // Concatenate with an empty grove
    emptyConcat->print();  // Expected: Hello
    delete emptyConcat;

    return 0;
}
