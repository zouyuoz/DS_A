#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::cin;
using std::cout;
using std::vector;

class Edge {
public:
    int u, v, w;
	// u, v: two vertexes; w: weight of the edge

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}

    // Overload the less-than operator to allow sorting by weight
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

// Disjoint Set Union (DSU) with path compression and union by rank
class DSU {
private:
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
			// Path compression
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) return;

		if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }

		return;
    }
};

bool isMSTValid(int V, const vector<Edge>& mstEdges) {
    std::set<int> vertices; // 使用 set 來存儲所有出現的頂點

    // 遍歷 MST 的所有邊，將邊的兩個端點加入 set
    for (const Edge& edge : mstEdges) {
        vertices.insert(edge.u);
        vertices.insert(edge.v);
    }

    // 檢查 set 中頂點的數量是否等於 V
    if (vertices.size() == V) {
        return true; // 覆蓋所有頂點，MST 有效
    }
    return false; // 未覆蓋所有頂點
}

// Main function to compute MST using Kruskal's Algorithm
void kruskalMST(int V, const vector<Edge>& edges) {
    DSU dsu(V);
    vector<Edge> mstEdges;
    int totalWeight = 0;

    // Sort edges by weight
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end());

    // Process edges in ascending order of weight
    for (const Edge& e : sortedEdges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mstEdges.push_back(e);
            totalWeight += e.w;
        }
    }

    // Output results
    cout << "Weight of Minimum Spanning Tree: " << totalWeight << "\n";
	cout << "Include all vertices: ";
	if (isMSTValid(V, mstEdges)) cout << "yes\n";
	else {cout << "no\n"; return;}
    cout << "Edges in the Minimum Spanning Tree:" << "\n";
    for (const Edge& e : mstEdges) {
        cout << e.u << " -- " << e.v << " [Weight: " << e.w << "]" << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges;

    cout << "Enter the edges (u, v, w) one by one:" << "\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    kruskalMST(V, edges);

    return 0;
}
