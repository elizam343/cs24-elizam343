#include "Stack.h"
#include "MyStack.h"

Stack* Stack::create() {
  // This will work if you use the obvious implementation.
  // Change it if you implement a different constructor!
  return new MyStack();
}
