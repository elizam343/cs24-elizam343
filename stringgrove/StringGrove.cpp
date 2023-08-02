#include "StringGrove.h"
#include "MyGrove.h"

template <typename T>
StringGrove<T>* StringGrove<T>::create(const char* s) {
  // This will work if you use the obvious implementation.
  // Change it if you implement a different constructor!
  return static_cast<StringGrove<T>> (new MyGrove(s));
}
