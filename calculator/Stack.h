#ifndef STACK_H
#define STACK_H

// This file describes the Stack interface you need to implement.
// Don't edit this!  Your code goes in the other files.

class Stack {
public:
  // Create and return a new stack.
  static Stack* create();

public:
  // These functions are "pure virtual" functions.
  // This means they're not implemented here, but your
  // subclass (MyStack) is required to implement them
  // in order to be a valid Stack.

  // Remove everything from the stack.
  virtual void clear() = 0;

  // Is this stack empty?
  virtual bool is_empty() const = 0;

  // Push an item onto the top of the stack.
  virtual void push(double item) = 0;

  // Pop an item off the top of the stack and return it.
  // If the stack is empty, throw std::underflow_error.
  virtual double pop() = 0;

  // Return the item currently on top of the stack.
  // If the stack is empty, throw std::underflow_error.
  virtual double top() const = 0;

  // Don't forget!
  virtual ~Stack() {}
};

#endif
