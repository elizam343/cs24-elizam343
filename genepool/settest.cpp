#include "SetOperators.h"
#include <iostream>

std::ostream& operator << (std::ostream& stream, const std::set<int>& data) {
  stream << "{ ";
  for(int x: data)
    stream << x << ' ';
  return stream << '}';
}

int main() {
  std::set<int> A{2, 3, 5, 7, 11, 13, 17, 19};
  std::set<int> B{1, 2, 3, 5, 8, 13, 21, 34};

  A |= B;

  std::cout << A << std::endl;
  std::cout << B << std::endl;
}
