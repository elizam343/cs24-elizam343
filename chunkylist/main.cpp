#include <iostream>
#include <cassert>
#include "MyChunkyList.h"

int main() {
    // Test Insert Invalid
    {
        MyChunkyList list(3);
        // Try to insert at an invalid index (greater than count)
        list.insert(1, "Invalid Item");
        // Assert that the list remains empty
        assert(list.count() == 0);
    }

    // Test Insert at Head
    {
        MyChunkyList list(4);
        list.insert(0, "First");
        list.insert(0, "Head Item");
        // Assert that "Head Item" is at the head of the list
        assert(list.lookup(0) == "Head Item");
        assert(list.lookup(1) == "First");
    }

    // Test Insert at Tail
    {
        MyChunkyList list(4);
        list.insert(0, "First");
        list.insert(list.count(), "Tail Item");
        // Assert that "Tail Item" is at the tail of the list
        assert(list.lookup(list.count() - 1) == "Tail Item");
        assert(list.lookup(list.count() - 2) == "First");
    }

    // Test Insert at Random
    {
        MyChunkyList list(4);
        list.insert(0, "First");
        list.insert(1, "Second");
        list.insert(1, "Random Item");
        // Assert that "Random Item" is at the correct index
        assert(list.lookup(1) == "Random Item");
        assert(list.lookup(0) == "First");
        assert(list.lookup(2) == "Second");
    }

    // Continue adding test cases for all other operations...

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
