#include "ChunkyList.h"
#include <iostream>
#include <cassert>
using namespace std;

// This is an example main file - it won't be graded.
// Use it to interact with your list and make sure it works!

int main() {
  ChunkyList* list = ChunkyList::create(5);

  assert(list->count() == 0);

  list->insert(0, "A");
  list->insert(1, "B");
  list->insert(0, "C");
  list->insert(2, "D");
  list->insert(4, "E");
  list->insert(3, "F");

  // Expected: C A D F E B
  cout << "List contents: ";
  for (int i = 0; i < list->count(); i++) {
    cout << list->lookup(i) << " ";
  }
  cout << endl;

  assert(list->count() == 6);
  assert(list->lookup(0) == "C");
  assert(list->lookup(1) == "A");
  assert(list->lookup(2) == "D");
  assert(list->lookup(3) == "F");
  assert(list->lookup(4) == "E");
  assert(list->lookup(5) == "B");

  list->remove(3);
  list->remove(0);

  // Expected: A D E B
  cout << "List contents after removal: ";
  for (int i = 0; i < list->count(); i++) {
    cout << list->lookup(i) << " ";
  }
  cout << endl;

  assert(list->count() == 4);
  assert(list->lookup(0) == "A");
  assert(list->lookup(1) == "D");
  assert(list->lookup(2) == "E");
  assert(list->lookup(3) == "B");

  delete list;

  cout << "All tests passed!" << endl;
  cout << "This program doesn't do anything yet...\n";

  //delete list;
}
