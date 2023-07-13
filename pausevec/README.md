# PauseVec

This is homework 2. It is due at 11:59, 07/14.

In this assignment,  you'll implement the _sequence_/_list_ abstract data type using a
_vector_/_dynamic array_ as the underlying concrete data type.  Unlike a standard vector,
which moves all elements whenever an element is removed, a PauseVec will not shift the elements
until an index greater than it is needed to be accessed.

## Example

If we start out with the vector \[ 1 2 3 4\], then first delete index 3, then delete index 1, and then index 1,
this should result first in \[ 1 2 3 X\], then in \[ 1 X 3 X\], and then when we try to access index 2, we first shift the elements of the array to be \[1 3 X X\], so that when we then try to delete index 1, we delete the 3, and the end result is \[1 X X X \], \[1 X\] after resizing.

Run `git pull upstream master` in your Git repo to get the starter code.

## Your Assignment

- Implement a vector that stores a sequence of `int`s.
- You can't use any container types from the standard library.
- Make sure your final code doesn't print anything.
- Make sure you don't have any memory leaks.


## The PauseVec Class

Implement your vector in a class called `PauseVec`.  Write the class definition in
`PauseVec.h` and implement the member functions in `PauseVec.cpp`.  Your vector must
obey the following rules:

- The vector must always have a capacity that is a power of 2.
- The vector must always have a capacity greater than or equal to `f(2) = 1`.
- When adding to a vector with capacity `f(n)`: if there is no room for the
  item, the vector must resize its capacity to double the capacity.
- When removing from a vector with capacity `f(n)`: if the number of elements shrinks
  below or equal to a quarter of the capacity, the vector must resize its capacity to halve the capacity.
- When reading, writing, or removing an element at a given index: if there have been deletions
  at less than or equal to that index since the last resize, shift every element over to be compact.


## Member Functions

Your `PauseVec` class must implement all of the following public member functions.
You can add private helper functions as well if it makes your life easier.

Values should be represented as `int`s  and sizes, indices, and counts should be
represented as `size_t`s. If a function doesn't modify your vector, mark it as a
`const` member function.

- The default constructor creates an empty vector with a capacity of 1.
- The destructor cleans up all allocated memory owned by the class.
- The `capacity` function returns the total size of the storage buffer.
- The `count` function returns the number of items stored in the vector.
- The `push` function takes one argument: a value.
  It adds the value to the end of the vector. It has no return value.
- The `lookup` function takes one argument: an index.  It returns the value
  stored at that index. If the index is invalid, it throws a `std::out_of_range`
  exception.
- The `mutate` function takes two arguments: an index and a value.  It changes the value
  stored at that index to the new value. If the index is invalid,
  it throws a `std::out_of_range` exception.
- The `remove` function takes one argument: an index. It removes and returns
  the value at the index. If the index is invalid, it throws a `std::out_of_range`
  exception.
- The `remove_val` function takes one argument: a value.
  It loops through and removes all copies of that value. It returns nothing.


## Hints

- Your vector should never resize by more than one step per function call.
- Write stubs for all the required member functions first. If your code compiles
  on Gradescope, you have the correct function signatures (regardless of whether
  or not you pass any of the other tests).
- If you get linker errors, you likely have the wrong function signatures.  Make
  sure that your class and function names are correct, and that you're using the
  correct parameter types and `const` qualifiers.
- Note that `size_t` is an unsigned integer type.  Don't subtract from zero!
