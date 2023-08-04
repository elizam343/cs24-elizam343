#include "MyGrove.h"
#include <iostream>

// Use this file to test your MyGrove class!
// This file won't be graded - do whatever you want.

int main() {
  MyGrove grove;
  grove.create("bro");
  grove.create("ken");
  grove.print(0);
  grove.print(1);
  grove.concat(0, 1);
  grove.print(2);
  

  return 0;
}
