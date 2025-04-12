#include <iostream>
#include <chrono>
using namespace std;

class SegmentTree {
private:
    int n;
    int* tree;

public:
    SegmentTree(const int* data, const int& size) {
        n = size; // size of primary data
        tree = new int[2 * n]; // the tree size
        Build(data);
    }

    ~SegmentTree() {
        delete[] tree;
    }

    void Build(const int* data) {
        // write data into leaf nodes
        for (int i = 0; i < n; ++i) {
            tree[n + i] = data[i];
        }
        // parent nodes, stores the larger element
        for (int i = n - 1; i > 0; --i) {
            tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    int Query(int left, int right) {
        left += n;
        right += n;
        int maximum = INT_MIN;

        while (left <= right) {
            if (left % 2 == 1) {
                maximum = std::max(maximum, tree[left]);
                ++left;
            }
            if (right % 2 == 0) {
                maximum = std::max(maximum, tree[right]);
                --right;
            }
            left /= 2;
            right /= 2;
        }
        return maximum;
    }
};

int maxValInQry(int* data, int l, int r) {
	int max = INT_MIN;
	for(int i = l; i <= r; ++i) {
		if (data[i] > max) max = data[i];
	}
	return max;
}

void run(int n, int queryCount) {
	cout << n << "\t" << queryCount << "\t";
	// generate data with size 10000
    int* data = new int[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 100000;
    }

    SegmentTree segTree(data, n);

    // generate 1000 queries
    int queries[queryCount][2];
    for (int i = 0; i < queryCount; i++) {
        int l = rand() % n;
        int r = l + (rand() % (n - l));
        queries[i][0] = l;
        queries[i][1] = r;
    }

    // measure segment tree method
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < queryCount; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        segTree.Query(l, r);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> segTreeTime = end - start;

    // measure straight forward method
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < queryCount; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        maxValInQry(data, l, r);
    }
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> bruteForceTime = end - start;

    // output time
    cout << segTreeTime.count() << " s\t";
    cout << bruteForceTime.count() << " s\n";

    delete[] data;
    return;
}

int main() {
	cout << "datas\tqueries\tSegment tree\tBrute search\n";
	int n = 10000;
	for (int i=1; i<=10; ++i){
		run(10*i*n, 50000);
	}

	return 0;
}