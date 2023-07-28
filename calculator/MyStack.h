#ifndef MYSTACK_H
#define MYSTACK_H

#include "Stack.h"
#include <vector>

class MyStack: public Stack {
private:
  std::vector<double> data;

  // TODO: Member Variables
public:
   MyStack();

  // Required Stack functions.
  // See Stack.h for descriptions.
  void   clear();
  bool   is_empty() const;
  void   push(double item);
  double pop();
  double top() const;

  // TODO: Add helper functions if necessary.
};

#endif
