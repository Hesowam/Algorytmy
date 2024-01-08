#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#define FILENAME "points1.txt"
#define SCALE 10
#define GRAPHVIZ_CMD "dot -Tpng g.gv -o file.png"

using namespace std;

struct point {
    double x, y;
    int index;
    double angle;
    bool is_start_point = false;

    point(int index, double xCoord, double yCoord) : index(index), x(xCoord), y(yCoord) {}
};

struct edge {
    int from;
    int to;

    edge(int fromIdx, int toIdx) : from(fromIdx), to(toIdx) {}
};

vector<point> read_file();
vector<edge> get_edges(stack<point> &points_stack);
bool is_left_rotate(point A, point B, point C);
point next_to_top(stack<point> &points_stack);
void sort_points_by_polar_angle(point *minimal, vector<point> &points);
point *find_minimal(vector<point> &points);
vector<edge> graham_scan(vector<point> &points);
void generate_graphviz(vector<edge> edges, vector<point> points);
void quick_sort(vector<point> &points, int left, int right);
int partition(vector<point> &points, int left, int right);

int main() {
    vector<point> points = read_file();
    vector<edge> edges = graham_scan(points);
    generate_graphviz(edges, points);
    return 0;
}


vector<edge> graham_scan(vector<point> &points) {
    point *minimal = find_minimal(points);
    stack<point> points_stack;

    sort_points_by_polar_angle(minimal, points);

    for (point p: points) {
        while (points_stack.size() > 2 && !is_left_rotate(next_to_top(points_stack), points_stack.top(), p)) {
            points_stack.pop();
        }
        points_stack.push(p);
    }

    return get_edges(points_stack);
}

vector<edge> get_edges(stack<point> &points_stack) {
    vector<point> points;
    vector<edge> edges;

    while (!points_stack.empty()) {
        points.push_back(points_stack.top());
        points_stack.pop();
    }

    std::reverse(points.begin(), points.end());

    for (int i = 0; i < points.size(); i++) {
        if (i == points.size() - 1) edges.emplace_back(points[i].index, points[0].index);
        else edges.emplace_back(points[i].index, points[i + 1].index);
    }

    return edges;
}

point next_to_top(stack<point> &points_stack) {
    point top = points_stack.top();
    points_stack.pop();
    point nextTop = points_stack.top();
    points_stack.push(top);
    return nextTop;
}

bool is_left_rotate(point A, point B, point C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x) > 0;
}

void sort_points_by_polar_angle(point *minimal, vector<point> &points) {
    for (point &p: points)
        p.angle = atan2((p.y - minimal->y), (p.x - minimal->x));
    quick_sort(points, 0, points.size() - 1);
}

point *find_minimal(vector<point> &points) {
    point *minimal = &points[0];
    for (point &p: points) {
        if ((p.y == minimal->y && p.x < minimal->x) || p.y < minimal->y) {
            minimal = &p;
        }
    }
    minimal->is_start_point = true;
    return minimal;
}

int partition(vector<point> &points, int left, int right) {
    point x = points[right];

    int left_index = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (points[j].angle <= x.angle) {
            left_index++;
            std::swap(points[left_index], points[j]);
        }
    }
    std::swap(points[left_index + 1], points[right]);
    return left_index + 1;
}

void quick_sort(vector<point> &points, int left, int right) {
    if (left >= right) return;
    int i = partition(points, left, right);
    quick_sort(points, left, i - 1);
    quick_sort(points, i + 1, right);
}


void generate_graphviz(vector<edge> edges, vector<point> points) {
    std::ofstream out("G.gv");

    if (out.is_open()) {
        out << "digraph {\n";
        out << "layout=neato;\n";
        out << "node [fontcolor=\"blue\"]\n";
        out << "node [label=\"\\N\", width=\"0.2\", height=\"0.2\", margin=\"0.01\"];\n";
        out << "label=\"scale x" << SCALE << "\";\n";

        for (point p: points) {
            out << p.index << " [fontsize=\"12\", pos=\"" << p.x * SCALE << "," << p.y * SCALE << "!\", shape="
                << (p.is_start_point ? "circle" : "plaintext") << "];\n";
        }
        for (edge e: edges) {
            out << e.from << " -> " << e.to << " [color=\"red\"];\n";
        }

        out << "\n}";
    }
    out.close();
    system(GRAPHVIZ_CMD);
}

vector<point> read_file() {
    vector<point> points;
    ifstream in(FILENAME);
    cout << "Opened file: " << FILENAME;

    int node_count;
    if (in.is_open()) {
        double x, y;
        in >> node_count;

        for (int i = 0; i < node_count; ++i) {
            in >> x >> y;
            points.emplace_back(i, x, y);
        }
    } else {
        cerr << "Failed to open file: " << FILENAME << endl;
    }

    in.close();
    return points;
}
