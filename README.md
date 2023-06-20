# Data-Structures-Library
This is a Data Structures Library that contains files for a Circular Dynamic Array, Red-Black Tree, Binary Heap, and Binomial Heap.
_The methods included in each data structure can be found in their respective folders: "cdainfo.pdf", "rbtinfo.pdf", "heapinfo.pdf"_

Circular Dynamic Array (CircularDynamicArray.cpp):
The CDA is a data structure that consists of _two_ concepts: Circular Arrays and Dynamic Arrays.
  Circular Array: An array in which the next element of the last element is the first element of the array.
  Dynamic Array: An array that resizes itself once 100% full (increase by double), or 25% full (decrease by half).

Red-Black Tree (RBTree.cpp):
The RBT is a variation of a balanced Binary Search Tree, with the following properties:
  1. Every node is either red or black.
  2. Every leaf (nil) is black.
  3. If a node is red, then both its children are black.
  4. Every simple path from a node to a descendant leaf contains the same number of black nodes.

Binary Heap (Heap.cpp):
A Binary Heap is a complete Binary Tree that satisfies the heap ordering property (Min Heap or Max Heap), usually represented using an array. The CDA that is included here will be used in Heap.cpp! The Binary heap featured in this library is a min heap.

Binomial Heap (BHeap.cpp):
A Binomial Heap is a set of Binomial Trees where each Binomial Tree follows the Min Heap property. There can be at most one Binomial Tree of any degree. Trees will merge together once more than one tree of each degree exists.
