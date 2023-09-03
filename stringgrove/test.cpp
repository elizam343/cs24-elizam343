#include <iostream>
#include "MyGrove.h"
#include <string>

void testGrove(const MyGrove& grove, const std::string& expected) {
    // Change 'length' to the correct function call.
    size_t len = grove.len(); // Assuming `len` is the function to get the length.
    if (len != expected.size()) {
        std::cerr << "Error: Expected length " << expected.size() << ", but got " << len << std::endl;
        return;
    }

    for (size_t i = 0; i < len; i++) {
        char ch = grove.charAt(i);
        if (ch != expected[i]) {
            std::cerr << "Error: Expected char '" << expected[i] << "' at index " << i << ", but got '" << ch << "'" << std::endl;
            return;
        }
    }

    std::cout << "Test Passed: Grove contains expected content '" << expected << "'" << std::endl;
}

int main() {
    MyGrove grove1("Hello");
    std::cout << "Length of grove1: " << grove1.len() << std::endl;
    
    MyGrove groveA("Hello");
    MyGrove groveB("World");
    MyGrove* groveCPtr = groveA.concat(&groveB);
    MyGrove groveC = *groveCPtr;
    testGrove(groveC, "HelloWorld");
    delete groveCPtr;

    MyGrove groveX("X");
    MyGrove groveY("Y");
    MyGrove groveZ("Z");
    MyGrove* groveXYPtr = groveX.concat(&groveY);
    MyGrove groveXY = *groveXYPtr;
    delete groveXYPtr;
    
    MyGrove* groveXYZPtr = groveXY.concat(&groveZ);
    MyGrove groveXYZ = *groveXYZPtr;
    testGrove(groveXYZ, "XYZ");
    delete groveXYZPtr;

    MyGrove groveEmpty("");
    MyGrove* groveDPtr = groveEmpty.concat(&groveA);
    MyGrove groveD = *groveDPtr;
    testGrove(groveD, "Hello");
    delete groveDPtr;

    return 0;
}
