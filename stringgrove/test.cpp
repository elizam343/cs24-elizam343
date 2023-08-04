#include "MyGrove.h"
#include <iostream>

// Use this file to test your MyGrove class!
// This file won't be graded - do whatever you want.

int main() {
  //MyGrove* stringtree = new MyGrove();

  const char* str1 = "apple";
  const char* str2 = "sauce";

  MyGrove* grove1 = new MyGrove(str1);
  MyGrove* grove2 = new MyGrove(str2);



  // Test len() function
  std::cout << "Length of grove1: " << grove1->len() << std::endl;
  std::cout << "Length of grove2: " << grove2->len() << std::endl;

  // Test concat() function
  const MyGrove* grove3 = grove1->concat(grove2);
  std::cout << "Concatenated grove1 and grove2: ";
  for (int i = 0; i < grove3->len(); i++) {
      std::cout << grove3->charAt(i);
  }
  std::cout << std::endl;

  // Test charAt() function
  std::cout << "Character at index 2 in grove3: " << grove3->charAt(2) << std::endl;

  // Test substr() function
  const MyGrove* grove4 = grove3->substr(1, 6);
  std::cout << "Substring of grove3: ";
  for (int i = 0; i < grove4->len(); i++) {
      std::cout << grove4->charAt(i);
  }
  std::cout << std::endl;

  // Clean up memory
  // delete grove1;
  // delete grove2;
  // delete grove3;
  // delete grove4;

  return 0;
}
