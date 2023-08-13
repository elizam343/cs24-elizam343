#include "Heap.h"
#include <stdexcept>  // for std::runtime_error
#include <algorithm>  // for std::min_element

Heap::Heap(size_t capacity) 
    : mCapacity(capacity), mCount(0), mData(new Entry[capacity]) {}

Heap::Heap(const Heap& other) 
    : mCapacity(other.mCapacity), mCount(other.mCount), mData(new Entry[other.mCapacity]) {
    for (size_t i = 0; i < mCount; i++) {
        mData[i] = other.mData[i];
    }
}

Heap::Heap(Heap&& other) 
    : mData(other.mData), mCapacity(other.mCapacity), mCount(other.mCount) {
    other.mData = nullptr;
    other.mCapacity = 0;
    other.mCount = 0;
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

const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::runtime_error("Index out of bounds");
    }
    return mData[index];
}

Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::runtime_error("Heap is empty");
    }

    // Find the entry with the smallest score
    auto it = std::min_element(mData, mData + mCount, [](const Entry& a, const Entry& b) {
        return a.score < b.score;
    });

    Entry minEntry = *it;

    // Replace the smallest entry with the last one
    *it = mData[mCount - 1];
    mCount--;

    return minEntry;
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        push(value, score);
        return {value, score};
    }

    // Find the entry with the smallest score
    auto it = std::min_element(mData, mData + mCount, [](const Entry& a, const Entry& b) {
        return a.score < b.score;
    });

    if (score < it->score) {
        return {value, score};
    }

    Entry minEntry = *it;

    // Replace the smallest score with the new entry
    *it = {value, score};

    return minEntry;
}

void Heap::push(const std::string& value, float score) {
    if (mCount >= mCapacity) {
        throw std::runtime_error("Heap is full");
    }

    mData[mCount++] = {value, score};
}

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::runtime_error("Heap is empty");
    }

    // Find the entry with the smallest score
    auto it = std::min_element(mData, mData + mCount, [](const Entry& a, const Entry& b) {
        return a.score < b.score;
    });

    return *it;
}
