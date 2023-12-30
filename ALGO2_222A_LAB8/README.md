# Kruskal algorithm and Union-Find structure

This program implements Kruskal's algorithm to find the minimum spanning tree in a graph. The program reads a graph from a text file, applies Kruskal's algorithm to find the minimum spanning tree, and saves the result in a format suitable for visualization using Graphviz.

## Main Components

- `graph`: A class representing the graph.
- `union_find` and `union_find_ranks`: Classes for managing sets of vertices when executing Kruskal's algorithm.
- `read_file()`: A function for reading the graph from a file.
- `save_graph()`: A function for saving the graph in DOT format for Graphviz.
- `kruskal()` and `kruskal2()`: Functions that implement Kruskal's algorithm, the first without using ranks, the second with ranks.

## Usage Instructions

### Requirements

To run the program, you need:

- A C++ compiler supporting the C++11 standard or higher.
- Graphviz installed for result visualization.

<a href="https://imgur.com/PG2XR7D"><img src="https://i.imgur.com/PG2XR7D.png" title="source: imgur.com" /></a>
<a href="https://imgur.com/7FDXhXl"><img src="https://i.imgur.com/7FDXhXl.png" title="source: imgur.com" /></a>
<a href="https://imgur.com/TjYia6p"><img src="https://i.imgur.com/TjYia6p.jpg" title="source: imgur.com" /></a>
