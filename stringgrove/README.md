# StringGrove

In this assignment you'll write an implementation of strings which allows
for efficient concatenation and space-efficient substrings.

## Structure of String Concatenations.

Imagine we have the strings "apple" and "sauce". We should then be able to create the concatenation of these two words into "applesauce" without using more than constant space by simply letting "applesauce" share its memory with "apple".
In order to make this possible, strings cannot be modified, but this is fine.

Now, if we take the substring of the first six characters of "applesauce" to get "apples", we can also save on space by sharing the "apple" part of "apples" with the string we already have - the "s" will have to have space allocated for it, but that's okay.

It turns out the best way of accomplishing this data sharing is with a binary tree.

## Your Assignment

- Implement a binary tree which stores strings in its leaves.
- Implement some basic string functions following the StringGrove.h signature.
- You can't use any container types from the standard library.
- Make sure you don't print anything that isn't explicitly allowed.

### Tree Data Structure

It is not mandatory, but you are strongly recommended to write a binary tree which follows the rules:

1. Each node is either a leaf or not.
2. Each leaf node has a non-null pointer to a character array (this is the normal string definition).
3. Each non-leaf node (we'll call it a join node) has two non-null pointers to nodes.
4. All nodes hold onto the length of the string they represent, which is all descendent leaf nodes
(including itself if appropriate) from left to right, concatenated.

### Functions:

You'll need to implement:
1. Efficient concatenation - O(1) worst-case time and space efficiency
2. Relatively efficient character lookup - O(h) worst-case time efficiency, where h is the number of concatenations performed.
3. Relatively time-and-space-efficient substring - it should take O(X + Y + h) space, where X is the number of existing strings that the substring is assembled out of, and Y is the number of remaining characters.
In the applesauce case above where we get the substring "apples" from it, X would be 1, because only "apple" was used, and Y would also be 1, because we only have "s" remaining, which is 1 character.

You will not need to implement:
* Mutation of strings
* Efficient printing or conversion to a normal string (you can do a simple print function by looping through indices and doing character lookup).
* A destructor (it would be rather complicated).

## Hints

* Implement first the binary tree structure, then concatenation, then character lookup, and finally substring.
* You will use the length field of nodes extensively in lookup and substring, and it must be set correctly in concatenation.
* Substring is the hardest function, it is most easily written recursively. First write a helper function for the leaf case,
and then a helper function for the join case.
* Consider that if the substring s' of s is entirely in the left child of s, then it is simply the same substring of the left child of s.
* If the substring s' of s spans both the left and  the right children of s, then the result should be a node with left child the section of s' in s's left child, and right child the section of s' in s's right child.
