#include "ChunkyList.h"
#include "MyChunkyList.h"

ChunkyList* ChunkyList::create(int chunksize) {
  // This will work if you use the obvious implementation.
  // Change it if you implement a different constructor!
  return new MyChunkyList(chunksize);
}
