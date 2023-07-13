#include "PauseVec.h"
#include <iostream>

PauseVec::PauseVec() {
    size = 1;
    size = 0;
    array = new int[size];
}

// Taking size from the user
PauseVec::PauseVec(int size)
{
    this -> size = size;
    array = new int[size];
    size = 0;
}
void PauseVec::grow () const{
    

}

int PauseVec::capacity () {
    if (size % 2 == 0) {
        return size;
        }
    else {
        size += 1;
        grow()
        return size;
    }
}

int PauseVec::count (int counter) {
    for (int i = 0; i < size; i++) {
        if (array[i] != -1) {
            // If element found return its index
            counter += 1;
            }
        }
    return counter;
}

void PauseVec::push (int val) {
    // check is array having size to store element or
    // not
    if (size == count) {

        // if not then grow the array by double
        grow();
    }
    // insert element
    array[size] = val;
    // increment the size or last_index+1
    size++;
}

int PauseVec::lookup (int index) {
    for (int i = 0; i < size; i++) {
            if (array[index] != NULL) {
                // If element found return its index
                return array[index];
            }
        }
    // Return -1 if element not found;
    return -1;
}


PauseVec::shrink() {
        // Creating new array of half size
        size = count;
        int* temp = new int[size];
 
        // copy element of old array in newly created array
        for (int i = 0; i < count; i++) {
            temp[i] = array[i];
        }
 
        // Delete old array
        delete[] array;
 
        // Assign newly created temp array to original array
        array = temp;
    
}
void PauseVec::mutate (int index, int val) const {

}
void PauseVec::remove (int index) const{
    for (int i = index; i < size; i++) {
            array[i] = array[i + 1];
        }
 
        // Replace the last index by 0
        array[size - 1] = 0;
 
        // Decrement the array size
        size--;
 
        // Reduce if the container half element of its
        // capacity
        if (size == (capacity / 2)) {
            shrink();
        }
}
void PauseVec::remove_val (int val) const {
    for (int i = 0; i < size; i++) {
            if (array[i] == val) {
                // If element found return its index
                return array[index];
            }
        }
    // Return -1 if element not found;
    return -1;

}