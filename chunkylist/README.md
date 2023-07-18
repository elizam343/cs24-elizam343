# Chunky List

_Due Wednesday, July 19th, before midnight Pacific Time._

In this assignment you'll implement a doubly-linked list.  This isn't your usual
doubly-linked list:  each node can store multiple items.  The `ChunkyList.h` and
`ChunkyNode.h` files describe the functions you'll need to implement.  The other
files are yours to edit as you wish.

You'll want to write a `main()` function so you can test your list, but don't do
this in the files provided  - add a new `.cpp` file.  This is for your use only,
and won't be tested.  Only the provided files will be compiled on Gradescope.


## Your Assignment

- Implement the `ChunkyNode` and `ChunkyList` interfaces.
- You can't use any container types from the standard library.
- Your list needs to obey the all of list rules listed below.
- Make sure you always have a valid doubly-linked list.
- Make sure you don't have any memory leaks!
- Don't print anything in your list code.


## List Rules

- Each list has a **chunk size** - this is the maximum  number of items that can
  be stored at any node in the list.  This will never change during the lifetime
  of the list, but different lists can have different chunk sizes.

- If you insert at the very beginning of a list (index 0)  and the first node is
  full, add a new node to hold the new value. The same applies to adding an item
  at the end of the list when the last node is full.

- Any other insert should go to the node that holds the index to be inserted at.
  If there's room in that node, simply insert the item.  If the node is full, it
  should **split** in two so that the new nodes are balanced _after_ the insert:

  - If there are an even number of items, both nodes should hold an equal number.
  - If there are an odd number of items, the first node should hold one more.

- If two adjacent nodes contain a total of (chunksize / 2) or fewer items, those
  nodes should **merge** into a single node. If any node could merge with either
  the previous or next node, always merge with the previous node.

- A list should never contain an empty node.


## Hints

- Don't rely on Gradescope for testing  -  write your own tests!  These won't be
  graded, but will save you a lot of time. The same goes for writing a Makefile.

- Having a `print()` function that shows what's stored in each Node will be very
  helpful when debugging.

- Make sure you remove any debug output from your list and node functions before
  submitting to Gradescope.  Unexpected output will confuse the autograder.

- A list can never have  any "empty" indices - the items in the tail of the list
  "slide around" to make or fill space as necessary.  For example,  if you start
  with this list:
  ```
  [0]: Patisar
  [1]: Caspar
  [2]: Melchior
  ```
  After calling `insert("Balthazar", 1)` you'll have:
  ```
  [0]: Patisar
  [1]: Balthazar
  [2]: Caspar
  [3]: Melchior
  ```
  And then, after calling `remove(0)` you'll get:
  ```
  [0]: Balthazar
  [1]: Caspar
  [2]: Melchior
  ```
