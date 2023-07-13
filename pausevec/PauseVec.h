#ifndef PAUSEVEC_H
#define PAUSEVEC_H

// This provides the size_t type:
#include <cstddef>

class PauseVec {
  
private:
  int* array = NULL;
  size_t size;
  size_t counter;

public:
  // Constructor
  PauseVec();
  void grow () const;
  int capacity ();
  int count (int counter);
  void push (int val);
  int lookup (int index);
  void shrink() const;
  void mutate (int index, int val) const;
  void remove (int index) const;
  void remove_val (int val) const;

  // Member Functions

};

// Used by the autograder:
PauseVec* create_pausevec();

PauseVec* create_pausevec() {
  return new PauseVec();
}

#endif
