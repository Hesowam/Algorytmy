//
// Created by Владимир Марянчук on 29/12/2023.
//

#ifndef ALGO2_222A_LAB8_UNION_FIND_H
#define ALGO2_222A_LAB8_UNION_FIND_H

#endif //ALGO2_222A_LAB8_UNION_FIND_H

class union_find_ranks {
private:
    int *parent;
    int *rank;
public:
    int find_counter = 0;

    union_find_ranks(int n) {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;
        if (rank[x] < rank[y])
            parent[x] = y;
        else {
            parent[y] = x;
            if (rank[x] == rank[y])
                rank++;
        }
    }

    int find(int x) {
        find_counter++;
        while (x != parent[x])
            x = parent[x];
        return x;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};