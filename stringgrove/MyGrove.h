#ifndef MYGROVE_H
#define MYGROVE_H

#include "StringGrove.h"

class MyGrove: public StringGrove<MyGrove> {
private:
  struct Node {
      const char* data; // Pointer to the character array
      int length; // Length of the string represented by this node
      Node* left;
      Node* right;
  };

  Node* root;

  // Helper function for recursive concatenation
  Node* concatNodes(Node* node1, Node* node2) const;

  // Helper function for recursive substring
  Node* substrNode(Node* node, int start, int end) const;

  // Helper function for recursive deletion of nodes
  void deleteNodes(Node* node);
  
public:
  MyGrove(const char* str);
  ~MyGrove();

  // Required StringGrove functions.
  // See StringGrove.h for descriptions.
  int     len() const;
  const MyGrove*    concat(MyGrove* other) const;
  char 	  charAt(int index) const;
  const MyGrove*    substr(int start, int end) const;

  // TODO: Add helper functions if necessary.
};

#endif
