//
// Created by Владимир Марянчук on 29/12/2023.
//

#ifndef ALGO2_222A_LAB8_UNION_FIND_H
#define ALGO2_222A_LAB8_UNION_FIND_H

#endif //ALGO2_222A_LAB8_UNION_FIND_H

class union_find {
private:
    int * parent;
public:
    int find_counter = 0;

    union_find(int n) {
         parent = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    void unite(int x, int y){
        x = find(x);
        y = find(y);

        if (x == y) return;
        parent[x] = y;
    }

    int find(int x){
        find_counter++;
        while (x != parent[x])
            x = parent[x];
        return x;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};