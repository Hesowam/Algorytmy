# Convex Hull Visualizer

This repository contains a C++ program designed to visualize the Convex Hull of a set of points. The program reads a set of points from a file, applies the Graham Scan algorithm to find the Convex Hull, and then generates a visualization using Graphviz.

## Main Components

- `struct point`: Represents a point with x, y coordinates, an index, and an angle for sorting.
- `struct edge` and `union_find_ranks`: Represents an edge between two points.
- `graham_scan`: Function to perform the Graham Scan algorithm.
- `generate_graphviz`: : Function to generate a Graphviz file for visualization.
- `quick_sort` and `partition`: Functions to sort points based on their polar angle.

## Usage Instructions

### Requirements

To run the program, you need:

- A C++ compiler supporting the C++11 standard or higher.
- Graphviz installed for result visualization.


<a href="https://imgur.com/FvWG6HB"><img src="https://i.imgur.com/FvWG6HB.png" title="source: imgur.com" /></a>
<a href="https://imgur.com/OWLYrAu"><img src="https://i.imgur.com/OWLYrAu.png" title="source: imgur.com" /></a>
<a href="https://imgur.com/XS3cPRT"><img src="https://i.imgur.com/XS3cPRT.png" title="source: imgur.com" /></a>
