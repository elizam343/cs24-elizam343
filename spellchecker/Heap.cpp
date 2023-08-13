#include "Heap.h"
#include <stdexcept>  // For exception handling

// Constructor
Heap::Heap(size_t capacity) 
    : mData(new Entry[capacity]), mCapacity(capacity), mCount(0) {}

// Copy constructor
Heap::Heap(const Heap& other) 
    : mData(new Entry[other.mCapacity]), mCapacity(other.mCapacity), mCount(other.mCount) {
    for (size_t i = 0; i < mCount; i++) {
        mData[i] = other.mData[i];
    }
}

// Move constructor
Heap::Heap(Heap&& other) 
    : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount) {
    other.mData = nullptr;
    other.mCount = 0;
    other.mCapacity = 0;
}


// Destructor
Heap::~Heap() {
    delete[] mData;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("Index out of range");
    }
    return mData[index];
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}

void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("Heap is full");
    }
    mData[mCount] = {value, score};
    mCount++;

    // Manual implementation of heapifyUp for min-heap
    size_t idx = mCount - 1;
    while (idx > 0) {
        size_t parentIdx = (idx - 1) / 2;
        if (mData[idx].score < mData[parentIdx].score) {
            Entry temp = mData[idx];
            mData[idx] = mData[parentIdx];
            mData[parentIdx] = temp;
            idx = parentIdx;
        } else {
            break;
        }
    }
}

Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }

    Entry poppedValue = mData[0];
    mData[0] = mData[mCount - 1];
    mCount--;

    // Manual implementation of heapifyDown for min-heap
    size_t idx = 0;
    while (true) {
        size_t leftIdx = 2 * idx + 1;
        size_t rightIdx = 2 * idx + 2;
        size_t smallest = idx;

        if (leftIdx < mCount && mData[leftIdx].score < mData[smallest].score) {
            smallest = leftIdx;
        }

        if (rightIdx < mCount && mData[rightIdx].score < mData[smallest].score) {
            smallest = rightIdx;
        }

        if (smallest != idx) {
            Entry temp = mData[idx];
            mData[idx] = mData[smallest];
            mData[smallest] = temp;
            idx = smallest;
        } else {
            break;
        }
    }

    return poppedValue;
}



Heap::Entry Heap::pushpop(const std::string& value, float score) {
    // If the heap is empty or the given score is less than the top score, 
    // simply return the given value and score without altering the heap.
    if (mCount == 0 || score < mData[0].score) {
        throw std::underflow_error("Heap is empty");
    }

    // If the score is greater than or equal to the top score, 
    // push the new value and pop the top value.
    push(value, score);
    return pop();
}


