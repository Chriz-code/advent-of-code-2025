#ifndef DSU_H
#define DSU_H

#include <vector>
#include <string>
#include <numeric>

struct Point3D {
    int id;
    long x, y, z;

    static std::string toString(Point3D& p) {
        return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ", " + std::to_string(p.z) + ")";
    }
};

struct Edge {
    int src, dest;
    double weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

//Disjoint Set Union with tracking (I copied this from the net)
class DSU {
private:
    std::vector<int> parent, rank;
    int numComponents;

public:
    DSU(int n) : numComponents(n) {
        parent.resize(n); rank.resize(n, 0); iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) std::swap(root_i, root_j);
            parent[root_j] = root_i;
            if (rank[root_i] == rank[root_j]) rank[root_i]++;
            numComponents--;
            return true;
        }
        return false;
    }
    int getNumComponents() const { return numComponents; }
};
#endif