//
// Created by Владимир Марянчук on 29/12/2023.
//

#include <vector>


#ifndef ALGO2_222A_LAB8_GRAPH_H
#define ALGO2_222A_LAB8_GRAPH_H

#endif //ALGO2_222A_LAB8_GRAPH_H


struct node {
    int index;
    double x, y;

    node(int idx, double xCoord, double yCoord) : index(idx), x(xCoord), y(yCoord) {}
};

struct edge {
    bool selected = false;
    int from;
    int to;
    double weight;

    edge(int f, int t, float w) : from(f), to(t), weight(w) {}
};

class graph{
public:
    std::vector<node> nodes;
    std::vector<edge> edges;

    void add_node(int index, double x, double y) {
        nodes.emplace_back(index, x, y);
    }

    void add_edge(int from, int to, double weight) {
        edges.emplace_back(from, to, weight);
    }

    void to_string(){
        double sum = 0;
        for (edge _edge: edges) {
            sum += _edge.weight;
        }
        std::cout << "\nNumber of edges " << edges.size() << ", sum of weights " << sum;
    }
};