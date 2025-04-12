#include <iostream>
#include <vector>
#include <limits>  // for numeric_limits(INF)
#include <algorithm> // for reverse
using namespace std;

// 改進後的 Edge 類別
class Edge {
public:
    int v; // 相鄰節點或優先佇列中的節點
    int w; // 邊的權重或距離

    Edge(int v, int w) : v(v), w(w) {}

    // 用於優先佇列的比較：基於 w（距離）
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

// 自訂優先佇列（最小堆）
template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parentIndex = (index - 1) / 2;
        if (heap[index] < heap[parentIndex]) { // 使用 operator< 進行比較
            std::swap(heap[index], heap[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) { smallest = leftChild; }
        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) { smallest = rightChild; }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void push(const T &value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    T top() const {
        if (heap.empty()) {
            throw std::out_of_range("Error: PriorityQueue is empty");
        }
        return heap[0];
    }

    bool empty() const { return heap.empty(); }
    int size() const { return heap.size(); }
};

// Dijkstra 演算法以找出從 source 到 target 的最短路徑
// 同時追蹤並返回路徑
pair<int, vector<int>> dijkstra(
	int source, int target, const vector<vector<Edge>> &adj
) {
    // 
    const int INF = numeric_limits<int>::max();
    vector<int> cost(adj.size(), INF);
    cost[source] = 0;
    vector<int> previousVertex(adj.size(), -1);

    PriorityQueue<Edge> pq;
    pq.push(Edge(source, 0));

    while (!pq.empty()) {
        Edge current = pq.top(); // vertex with smallest cost
        pq.pop();

        int currentDist = current.w;
        int u = current.v;

        // 如果已經到達目標節點，停止
        // 如果這個距離不是最新的，跳過
        if (u == target) break;
        if (currentDist > cost[u]) continue;

        // 探索相鄰節點
        for (const auto &edge : adj[u]) {
            int v = edge.v;
            int weight = edge.w;

            if (cost[u] != INF && cost[u] + weight < cost[v]) {
                cost[v] = cost[u] + weight;
                previousVertex[v] = u;
                pq.push(Edge(v, cost[v]));
            }
        }
    }

    // 如果目標節點不可達
    if (cost[target] == INF) return { -1, {} };

    // 重建路徑
    vector<int> path;
    int current = target;
    while (current != -1) {
        path.push_back(current);
        current = previousVertex[current];
    }
    std::reverse(path.begin(), path.end());

    return { cost[target], path };
}

int main() {
    int numEdges;
    cin >> numEdges;

    // 構建鄰接表
    vector<vector<Edge>> adj(15, vector<Edge>());
    int u, v, w;
    int maxVertex = 0;

    // 讀取所有邊並找出最大節點索引
    for (int i = 0; i < numEdges; ++i) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        maxVertex = max(maxVertex, max(u, v));
    }

    int source = 0;
    int target = maxVertex;

    pair<int, vector<int>> result = dijkstra(source, target, adj);

    if (result.first == -1) {
		cout << "There is no path from vertex " << source
			 << " to vertex " << target << "." << endl;
		return 0;
	}

    cout << "Shortest path cost: " << result.first << endl;

    // 列出經過的所有邊
    cout << "Edges in the path:" << endl;
    for (size_t i = 1; i < result.second.size(); ++i) {
        int from = result.second[i - 1];
        int to = result.second[i];
        // 在鄰接表中找到邊的權重
        int weight = -1;
        for (const auto &edge : adj[from]) {
            if (edge.v == to) {
                weight = edge.w;
                break;
            }
        }
        cout << from << " --(" << weight << ")--> " << to << endl;
    }
    
    return 0;
}
