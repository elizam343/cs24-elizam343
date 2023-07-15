#include "PauseVec.h"

PauseVec::PauseVec() {
    size_capacity = 1;  
    count_elements = 0;
    last_resize_index = 0;
    size = new int[size_capacity];  
}

PauseVec::~PauseVec() {
    delete[] size;  
}

size_t PauseVec::capacity() const {
    return size_capacity;  
}

size_t PauseVec::count() const {
    return count_elements;
}

void PauseVec::push(int value) {
    if (count_elements == size_capacity)
        resize(size_capacity * 2);

    size[count_elements++] = value;  
}

int PauseVec::lookup(size_t index) {
    if (index >= count_elements)
        throw std::out_of_range("Index out of range");

    return size[index];
}

void PauseVec::mutate(size_t index, int value) {
    if (index >= count_elements)
        throw std::out_of_range("Index out of range");

    size[index] = value;  
}

int PauseVec::remove(size_t index) {
    if (index >= count_elements)
        return -1;

    int value = size[index];  
    for (size_t i = index; i < count_elements - 1; i++)
        size[i] = size[i + 1];  

    count_elements--;

    if (count_elements <= size_capacity / 4)
        resize(size_capacity / 2);

    return value;
}

void PauseVec::remove_val(int value) {
    for (size_t i = 0; i < count_elements; i++) {
        if (size[i] == value)  
        {
            remove(i);
            i--;  
        }
    }
}

void PauseVec::resize(size_t new_size) {
    int* new_cap = new int[new_size];

    for (size_t i = 0; i < count_elements; i++)
        new_cap[i] = size[i];

    delete[] size;
    size = new_cap;
    size_capacity = new_size;

    if (last_resize_index >= count_elements)
        last_resize_index = 0;
}

void PauseVec::shrink() {
    if (last_resize_index < count_elements) {
        for (size_t i = last_resize_index; i < count_elements - 1; i++)
            size[i] = size[i + 1];  

        last_resize_index = count_elements;
    }
}