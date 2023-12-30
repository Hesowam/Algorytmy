#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"
#include "union_find.h"
#include "union_find_ranks.h"

#define FILENAME "g2.txt"
#define SCALE 10
#define GRAPHVIZ_CMD "dot -Tpng g.gv -o file.png"

using namespace std;

void save_graph(graph &G) {
    std::ofstream out("G.gv");

    if (out.is_open()) {
        out << "graph {\n";
        out << "layout=neato;\n";
        out << "node [fontcolor=\"blue\"]\n";
        out << "node [label=\"\\N\", width=\"0.2\", height=\"0.2\", margin=\"0.01\"];\n";
        out << "node [shape=plaintext]\n";
        out << "label=\"scale x" << SCALE << "\";\n";

        for (node _node: G.nodes) {
            out << _node.index << " [fontsize=\"12\", pos=\"" << _node.x * SCALE << "," << _node.y * SCALE << "!\"];\n";
        }
        for (edge _edge: G.edges) {
            string color = _edge.selected ? "red" : "grey";
            out << _edge.from << " -- " << _edge.to << " [weight=\"" << _edge.weight << "\", color=\"" << color
                << "\"];\n";
        }

        out << "\n}";
    }
    out.close();
    system(GRAPHVIZ_CMD);
}

graph read_file() {
    graph G;
    ifstream in(FILENAME);

    int node_count;

    if (in.is_open()) {
        double x, y;
        in >> node_count;

        for (int i = 0; i < node_count; ++i) {
            in >> x >> y;
            G.add_node(i, x, y);
        }
        int graphs_link_count;
        in >> graphs_link_count;

        for (int i = 0; i < graphs_link_count; ++i) {
            int first_index, second_index;
            double weight;
            in >> first_index >> second_index >> weight;
            G.add_edge(first_index, second_index, weight);
        }
    }

    in.close();
    return G;
}

void swap(std::vector<edge> &edges, int left_index, int right_index) {
    std::swap(edges[left_index], edges[right_index]);
}

int partition(std::vector<edge> &edges, int left, int right) {
    edge x = edges[right];
    int left_index = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (edges[j].weight <= x.weight) {
            left_index++;
            std::swap(edges[left_index], edges[j]);
        }
    }
    std::swap(edges[left_index + 1], edges[right]);
    return left_index + 1;
}

void quick_sort(std::vector<edge> &edges, int left, int right) {
    if (left >= right) return;
    int i = partition(edges, left, right);
    quick_sort(edges, left, i - 1);
    quick_sort(edges, i + 1, right);
}

graph kruskal2(graph &G) {
    cout << "Union find ranks\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    quick_sort(G.edges, 0, G.edges.size() - 1);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Using fast sorting " << G.edges.size() << " edges sorted for "
              << std::setw(9) << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";

    graph T;
    T.nodes = G.nodes;
    union_find_ranks ufr = *new union_find_ranks(G.nodes.size());

    t1 = std::chrono::high_resolution_clock::now();
    for (edge &_edge: G.edges) {
        if (!ufr.connected(_edge.from, _edge.to)) {
            T.add_edge(_edge.from, _edge.to, _edge.weight);
            ufr.unite(_edge.from, _edge.to);
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "The algorithm is executed for " << std::chrono::duration<double, std::milli>(t2 - t1).count()
              << " ms\n";
    cout << "Number of executions of the find operation: " << ufr.find_counter;
    return T;
}

graph kruskal(graph &G) {
    cout << "Union find without ranks\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    quick_sort(G.edges, 0, G.edges.size() - 1);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Using fast sorting " << G.edges.size() << " edges sorted for "
              << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";

    graph T;
    T.nodes = G.nodes;
    union_find uf(G.nodes.size());

    t1 = std::chrono::high_resolution_clock::now();
    for (edge &_edge: G.edges) {
        if (!uf.connected(_edge.from, _edge.to)) {
            _edge.selected = true;
            T.add_edge(_edge.from, _edge.to, _edge.weight);
            uf.unite(_edge.from, _edge.to);
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "The algorithm is executed for " << std::chrono::duration<double, std::milli>(t2 - t1).count()
              << " ms\n";
    cout << "Number of executions of the find operation: " << uf.find_counter;
    return T;
}

int main() {
    graph G = read_file();
    graph T = kruskal(G); //without ranks
//    kruskal2(G); // with ranks
    T.to_string();
    save_graph(G);
    return 0;
}
