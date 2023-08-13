#include "Heap.h"

// Constructor
Heap::Heap(size_t capacity) 
    : mCapacity(capacity), mCount(0), mData(new Entry[capacity]) {}

// Copy constructor
Heap::Heap(const Heap& other) 
    : mCapacity(other.mCapacity), mCount(other.mCount), mData(new Entry[other.mCapacity]) {
    for (size_t i = 0; i < mCount; i++) {
        mData[i] = other.mData[i];
    }
}

// Move constructor
Heap::Heap(Heap&& other) 
    : mCapacity(other.mCapacity), mCount(other.mCount), mData(other.mData) {
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
        throw std::out_of_range("Heap is empty");
    }
    return mData[0];
}

void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("Heap is full");
    }
    mData[mCount] = {value, score};
    mCount++;

    // Manual implementation of heapifyUp
    size_t idx = mCount - 1;
    while (idx > 0) {
        size_t parentIdx = (idx - 1) / 2;
        if (mData[idx].score > mData[parentIdx].score) {
            std::swap(mData[idx], mData[parentIdx]);
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

    // Manual implementation of heapifyDown
    size_t idx = 0;
    while (true) {
        size_t leftChildIdx = 2 * idx + 1;
        size_t rightChildIdx = 2 * idx + 2;
        size_t largest = idx;

        if (leftChildIdx < mCount && mData[leftChildIdx].score > mData[largest].score) {
            largest = leftChildIdx;
        }

        if (rightChildIdx < mCount && mData[rightChildIdx].score > mData[largest].score) {
            largest = rightChildIdx;
        }

        if (largest != idx) {
            std::swap(mData[idx], mData[largest]);
            idx = largest;
        } else {
            break;
        }
    }

    return poppedValue;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0 || score > mData[0].score) {
        push(value, score);
        return pop();
    }
    return {value, score};
}
