#include "Heap.h"
#include "WordList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

void test_basic_push_pop() {
    Heap heap(5);
    heap.push("apple", 5.5);      // Heap: apple(5.5)
    heap.push("banana", 6.6);     // Heap: apple(5.5), banana(6.6)
    
    assert(heap.count() == 2);
    assert(heap.top().value == "apple");

    Heap::Entry entry = heap.pop();
    assert(entry.value == "apple"); // Since "apple" is smaller, it should be the one that is popped first
    assert(heap.count() == 1);
    assert(heap.top().value == "banana"); // Now, the top should be "banana" since "apple" has been popped off
    std::cout << "Test 1: Basic push and pop passed!\n";
}

void test_heap_max_capacity() {
    Heap heap(5);
    heap.push("apple", 5.5);
    heap.push("banana", 6.6);
    heap.push("cherry", 7.7);
    heap.push("date", 8.8);
    heap.push("elderberry", 9.9);

    // The smallest values should be at the top in the order apple, banana, cherry, date, elderberry
    assert(heap.count() == 5);
    try {
        heap.push("fig", 4.0);  // Should replace "elderberry" since 4.0 < 5.5 and heap capacity is 5
        assert(false);
    } catch(const std::overflow_error& e) {
        // Expected this exception
    }
    std::cout << "Test 2: Heap max capacity passed!\n";
}


void test_pop_empty_heap() {
    Heap heap(5);
    try {
        heap.pop();
        assert(false);
    } catch(const std::underflow_error& e) {
        // Expected this exception
    }
    std::cout << "Test 3: Pop from empty heap passed!\n";
}

void test_pushpop_behavior() {
    Heap heap(5);
    heap.push("grape", 11.0);
    Heap::Entry pushpopEntry = heap.pushpop("honeydew", 12.0);
    assert(pushpopEntry.value == "grape");
    assert(heap.top().value == "honeydew"); 
    std::cout << "Test 4: Push-pop behavior passed!\n";
}

void test_copy_constructor() {
    Heap heap1(5);
    heap1.push("grape", 11.0);
    Heap heap2(heap1);
    assert(heap1.top().value == heap2.top().value);
    assert(heap1.count() == heap2.count());
    std::cout << "Test 5: Copy constructor passed!\n";
}

void test_move_constructor() {
    Heap heap1(5);
    heap1.push("grape", 11.0);
    Heap heap2(std::move(heap1));
    assert(heap2.top().value == "grape");
    assert(heap2.count() == 1);
    assert(heap1.count() == 0);
    std::cout << "Test 6: Move constructor passed!\n";
}

void test_empty_stream() {
    std::istringstream stream("");
    WordList wordList(stream);
    std::vector<Point> points = {/* Some random points */};
    Heap result = wordList.correct(points, 5, 0.5);
    assert(result.count() == 0);
    std::cout << "Test: Empty input stream passed!\n";
}

void test_uppercase_words() {
    std::istringstream stream("Hello World");
    WordList wordList(stream);
    std::vector<Point> points = {/* Some random points of length 5 */};
    Heap result = wordList.correct(points, 5, 0.5);
    assert(result.count() == 0); // Assuming none of the words match in length and point count.
    std::cout << "Test: Uppercase words passed!\n";
}

void test_number_symbol_words() {
    std::istringstream stream("123 !@#");
    WordList wordList(stream);
    std::vector<Point> points = {/* Some random points of length 3 */};
    Heap result = wordList.correct(points, 5, 0.5);
    assert(result.count() == 0); // None of the words should match as they have numbers/symbols.
    std::cout << "Test: Numbers and symbols words passed!\n";
}

void test_empty_points() {
    std::istringstream stream("apple banana cherry");
    WordList wordList(stream);
    Heap result = wordList.correct({}, 5, 0.5); // Passing empty points vector
    assert(result.count() == 0);
    std::cout << "Test: Empty points passed!\n";
}

void test_mismatched_word_point_lengths() {
    std::istringstream stream("apple cherry");
    WordList wordList(stream);
    std::vector<Point> points = {/* Some random points of length 3 */}; // mismatched length
    Heap result = wordList.correct(points, 5, 0.5);
    assert(result.count() == 0); 
    std::cout << "Test: Mismatched word and point lengths passed!\n";
}

void test_large_word_prediction() {
    std::istringstream stream("supercalifragilisticexpialidocious antidisestablishmentarianism pneumonoultramicroscopicsilicovolcanoconiosis");
    WordList wordList(stream);
    
    // Dummy keypress points for the word "supercalifragilisticexpialidocious"
    // Assuming each character's Point is an exact match on the QWERTY layout
    std::vector<Point> points = {/* Fill with the QWERTY Point coordinates for each character in "supercalifragilisticexpialidocious" */};

    // Populate the points vector with the QWERTY Point values for "supercalifragilisticexpialidocious"
    for (char c : "supercalifragilisticexpialidocious") {
        points.push_back(QWERTY[c - 'a']);
    }

    Heap result = wordList.correct(points, 5, 0.5);
    
    // Ensure the top predicted word matches the word "supercalifragilisticexpialidocious"
    assert(result.top().value == "supercalifragilisticexpialidocious");
    
    std::cout << "Test: Large word prediction passed!\n";
}



int main() {
    // Add the new test functions here
    test_empty_stream();
    test_uppercase_words();
    test_number_symbol_words();
    test_empty_points();
    test_mismatched_word_point_lengths();
    test_large_word_prediction();

    test_basic_push_pop();
    test_heap_max_capacity();
    test_pop_empty_heap();
    test_pushpop_behavior();
    test_copy_constructor();
    test_move_constructor();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}