#include <iostream>
#include "MyGrove.h"

int main() {
    MyGrove grove;

    // 1. Create "abc"
    grove.create("abc");
    std::cout << "Node 1: ";
    grove.print(0);  // Node 1 is at index 0
    std::cout << std::endl;

    // 2. Create "def"
    grove.create("def");
    std::cout << "Node 2: ";
    grove.print(1);  // Node 2 is at index 1
    std::cout << std::endl;

    // 3. Concat 1 and 2
    grove.concat(0, 1);
    std::cout << "Node 3 (Node 1 + Node 2): ";
    grove.print(2);  // Node 3 is at index 2
    std::cout << std::endl;

    // 4. Concat 3 and 1
    grove.concat(2, 0);
    std::cout << "Node 4 (Node 3 + Node 1): ";
    grove.print(3);  // Node 4 is at index 3
    std::cout << std::endl;

    // 5. Substr 3 from index 0 to 4
    MyGrove* substrGrove1 = grove.substr(2, 0, 4);
    std::cout << "Substring of Node 3 from index 0 to 4: ";
    substrGrove1->print(0);  // Substring is at index 0
    std::cout << std::endl;
    delete substrGrove1;

    // 6. Substr 3 from index 2 to 6
    MyGrove* substrGrove2 = grove.substr(2, 2, 6);
    std::cout << "Substring of Node 3 from index 2 to 6: ";
    substrGrove2->print(0);  // Substring is at index 0
    std::cout << std::endl;
    delete substrGrove2;

    // 7. Substr 4 from index 2 to 9
    MyGrove* substrGrove3 = grove.substr(3, 2, 9);
    std::cout << "Substring of Node 4 from index 2 to 9: ";
    substrGrove3->print(0);  // Substring is at index 0
    std::cout << std::endl;
    delete substrGrove3;

    return 0;
}
