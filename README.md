# Data-Structures-Library
This is a refreshed version of my Data Structures Library project that I worked on in my CS 201 (Data Structures & Algorithms) class. This repository contains files for a Circular Dynamic Array, Red-Black Tree, Binary Heap, and Binomial Heap. All of these Data Structures include additional methods for functionality.

**Manually coding Data Structures for this project provided me with quite the challenge, however I feel that it was a valuable experience which allowed me to strengthen my programming skills and understanding of DSA. I managed a project average of 83.7%, but decided to challenge myself once again after a few months with this refresh!**

Circular Dynamic Array (CircularDynamicArray.cpp): <br />
_Original code decreased by 52%_ <br />
<br />
The CDA is a data structure that consists of _two_ concepts: Circular Arrays and Dynamic Arrays. <br />
  Circular Array: An array in which the next element of the last element is the first element of the array. <br />
  Dynamic Array: An array that resizes itself once 100% full (increase by double), or 25% full (decrease by half). <br />

Red-Black Tree (RBTree.cpp):<br />
_Original code decreased by 40%_<br />
<br />
The RBT is a variation of a balanced Binary Search Tree, with the following properties:<br />
  1. Every node is either red or black.
  2. Every leaf (nil) is black.
  3. If a node is red, then both its children are black.
  4. Every simple path from a node to a descendant leaf contains the same number of black nodes.
<br />
Binary Heap (Heap.cpp):<br />
A Binary Heap is a complete Binary Tree that satisfies the heap ordering property (Min Heap or Max Heap), usually represented using an array. The CDA that is included here will be used in Heap.cpp! The Binary heap featured in this library is a min heap.
<br />
Binomial Heap (BHeap.cpp):<br />
<br />
A Binomial Heap is a set of Binomial Trees where each Binomial Tree follows the Min Heap property. There can be at most one Binomial Tree of any degree. Trees will merge together once more than one tree of each degree exists.
