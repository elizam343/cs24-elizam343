#include "Heap.h"
#include <iostream>
#include <cassert>

int main() {
    // Test 1: Basic push and pop
    Heap heap(5);
    heap.push("apple", 5.5);
    heap.push("banana", 6.6);
    assert(heap.count() == 2);
    assert(heap.top().value == "banana");
    
    Heap::Entry entry = heap.pop();
    assert(entry.value == "banana");
    assert(heap.count() == 1);

    // Test 2: Heap max capacity
    heap.push("cherry", 7.7);
    heap.push("date", 8.8);
    heap.push("elderberry", 9.9);
    
    // Now the heap should be full
    assert(heap.count() == 5);
    try {
        heap.push("fig", 10.0);  // this should throw an overflow error
        assert(false); // If we reach here, the test has failed.
    } catch(const std::overflow_error& e) {
        // expected this exception
    }

    // Test 3: Pop from empty heap
    Heap emptyHeap(5);
    try {
        emptyHeap.pop();  // this should throw an underflow error
        assert(false); // If we reach here, the test has failed.
    } catch(const std::underflow_error& e) {
        // expected this exception
    }

    // Test 4: Push-pop behavior
    Heap heap2(5);
    heap2.push("grape", 11.0);
    Heap::Entry pushpopEntry = heap2.pushpop("honeydew", 12.0);
    assert(pushpopEntry.value == "grape");
    assert(heap2.top().value == "honeydew");

    // Test 5: Copy constructor
    Heap heap3(heap2);
    assert(heap2.top().value == heap3.top().value);
    assert(heap2.count() == heap3.count());

    // Test 6: Move constructor
    Heap heap4(std::move(heap3));
    assert(heap4.top().value == "honeydew");
    assert(heap4.count() == 1);
    assert(heap3.count() == 0); // since it's moved

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
