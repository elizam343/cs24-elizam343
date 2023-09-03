#include <iostream>
#include "MyGrove.h"

int main() {
    // Test case 1: Create a MyGrove with a string and get its length
    MyGrove* grove1 = new MyGrove("Hello");
    std::cout << "Length of grove1: " << grove1->len() << std::endl;  // Expected: 5

    // Test case 2: Fetch a character at a particular index
    try {
        char ch = grove1->charAt(1);
        std::cout << "Character at index 1 of grove1: " << ch << std::endl;  // Expected: e
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test case 3: Fetch a substring from grove1
    try {
        MyGrove* subGrove = grove1->substr(1, 4); // Should extract "ell"
        std::cout << "Substring of grove1 from index 1 to 3: " << subGrove->toString() << std::endl; // Expected: ell
        delete subGrove;
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test case 4: Out-of-range character fetch
    try {
        char ch = grove1->charAt(10);
        std::cout << "Character at index 10 of grove1: " << ch << std::endl;  // This should not be reached
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;  // Expected: Index out of range
    }

    // Cleanup
    delete grove1;

    return 0;
}
