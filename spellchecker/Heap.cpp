#include "Heap.h"
#include <stdexcept>

Heap::Heap(size_t capacity) : mCapacity(capacity), mCount(0) {
    mData = new Entry[capacity];
}

Heap::Heap(const Heap& other) : mCapacity(other.mCapacity), mCount(other.mCount) {
    mData = new Entry[mCapacity];
    std::copy(other.mData, other.mData + other.mCount, mData);
}

Heap::Heap(Heap&& other) : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount) {
    other.mData = nullptr;
    other.mCapacity = other.mCount = 0;
}

Heap::~Heap() {
    delete[] mData;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::runtime_error("Heap is empty");
    }
    return mData[0];
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("Index out of range");
    }
    return mData[index];
}

Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::runtime_error("Heap is empty");
    }
    Entry top = mData[0];
    mData[0] = mData[--mCount];
    heapifyDown(0);
    return top;
}

void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::runtime_error("Heap is full");
    }
    mData[mCount++] = {value, score};
    heapifyUp(mCount - 1);
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    // Check if the heap is empty
    if (mCount == 0) {
        push(value, score);
        return top();
    }
    
    Heap::Entry topEntry = top();
    
    if (score < topEntry.score) {
        mData[0] = {value, score};
        heapifyDown(0);  // Make sure to define and implement this function.
    }
    return top();
}


void Heap::heapifyUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (mData[parent].score <= mData[index].score) break;
        std::swap(mData[parent], mData[index]);
        index = parent;
    }
}

void Heap::heapifyDown(size_t index) {
    while (index * 2 + 1 < mCount) {
        size_t child = index * 2 + 1;
        if (child + 1 < mCount && mData[child + 1].score < mData[child].score) {
            child++;
        }
        if (mData[child].score >= mData[index].score) break;
        std::swap(mData[child], mData[index]);
        index = child;
    }
}
