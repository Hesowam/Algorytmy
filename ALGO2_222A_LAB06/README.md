# Algorithms Laboratory: Binary Heap
**Przemysław Klęsk | September 30, 2019**

The goal of the task is to implement a data structure called a binary heap. A maximum-oriented binary heap is a binary tree where each node has a key greater than or equal to the keys of its children. The typical implementation of a heap is based on a dynamic array, where the nodes of the binary tree representing the heap are inserted level by level.

### Heap Conditions
- All levels of the heap except the last one must be full.
- Simple arithmetic operations allow determining the index of a parent node and the indices of its children. With zero-based indexing, the parent of node `i` is at index ⌊(i − 1)/2⌋, and the children are at indices 2i + 1 and 2i + 2.

### Heap Applications
1. Heap Sort
2. Finding shortest paths (e.g., Dijkstra's and A∗ algorithms)

### Analyzed Operations
The execution times of two crucial operations on the heap will be examined:
- Adding a new element
- Retrieving the maximum element (poll operation)

Both of these operations have a computational complexity of O(log n), leading to a time complexity of O(n log n) for n elements.

### Note
Heap sorting will not be implemented in this task. Additional functions needed for this purpose will appear in a later task comparing heap sort with other methods.

### Implementation
- The implementation can utilize a previously created custom dynamic array container.
- The binary heap interface should provide functions/methods such as:
  - Adding a new element
  - Retrieving and removing the maximum element
  - Clearing the heap
  - Returning a string representation of the heap
  - Recursive upward heapify
  - Recursive downward heapify

### Tips
- Dynamic memory management (new, delete)
- Implementation of the heap interface in a separate .h file
- Working with strings (using std::string)
- Time measurement (using the clock() function after including #include <time.h>)
- Using function pointers
- Generating random data (using rand() and srand(...))
