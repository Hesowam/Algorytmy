# Algorithms 2 Laboratory: Linked List Implementation

## Task
The goal is to implement a data structure called a linked list, which is one of the most basic linear data structures. The chosen variant will be a doubly linked list. Each node in the list will contain three pieces of information:
- Actual data (record, object) or a pointer to it
- Pointer to the previous element
- Pointer to the next element

The list itself will store pointers to the first and last elements (head and tail) and its current size.

The additional goal is to measure the computational complexity of operations on the list, such as adding, searching, and deleting elements, especially with an increasing number of stored elements.

## Implementation Guidelines
- The implementation can be done structurally or object-oriented, utilizing the template mechanism available in C++.
- The list should be able to store structures containing at least two simple data fields.
- The interface should include functions/methods for various operations on the list.

## Interface Functions/Methods
1. Add a new element at the end of the list (data as an argument)
2. Add a new element at the beginning of the list (data as an argument)
3. Remove the last element
4. Remove the first element
5. Return data of the i-th element in the list (index as an argument)
6. Set (replace) data of the i-th element in the list (index and new data as arguments)
7. Find an element in the list (search key and comparator as arguments)
8. Find and remove an element in the list (search key and comparator as arguments)
9. Add a new element with forced order (data and comparator as arguments)
10. Clear the list (remove all elements)
11. Return the string representation of the list

## Additional Notes
- Memory management should be handled appropriately.
- Consider who is responsible for freeing the memory associated with the stored data (either the list or external places where data is created).
- The main function should include an experiment that involves adding elements to the list, searching, and deleting random data with time measurements.
- The code should be sent for anti-plagiarism checks to algo2@zut.edu.pl following specific naming and format guidelines.

## Main Function Experiment
The main experiment involves adding an increasing number of elements to the list, performing searches and deletions, and measuring the time.
