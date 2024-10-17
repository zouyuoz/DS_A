#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

// for output colored map
void SetColor(int color = 7) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
}

// implement queue structure
template<typename T>
class Queue {
private:
	vector<T> data;
	size_t frontIndex;
	size_t size;

public:
	Queue(): frontIndex(0), size(0) {}

	bool empty() { return !size; }

	void push(const T& item){
		data.push_back(item);
		size++;
	}

	T pop() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		T item = data[frontIndex];
		// update frontIndex and size of vector 
		frontIndex++;
		size--;
		
		// Reset the queue when it's empty to save space
		if (empty()) {
			data.clear();
			frontIndex = 0;
		}
		
		return item;
	}

	T& front() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		return data[frontIndex];
	}
};

// Directions
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct Node {
	int x, y;
	Node(int x = 0, int y = 0): x(x), y(y) {}
	bool operator ==(Node &other) { return x == other.x && y == other.y; }
};

class Maze {
private:
	vector<vector<char>> maze;
	int m, n;
	Node start, end;
	vector<Node> backTracePath(const vector<vector<Node>>& parent);
	void drawColoredPath();

public:
	Maze(int m, int n) : m(m), n(n) {
		maze = vector<vector<char>>(m, vector<char>(n, '0'));
	}
	void setCell(int x, int y, char type);
	vector<Node> findShortestPath();
};

void Maze::setCell(int x, int y, char type) {
	maze[x - 1][y - 1] = type;
	if (type == 's') start = Node(x - 1, y - 1);
	if (type == 't') end = Node(x - 1, y - 1);
}

vector<Node> Maze::findShortestPath() {
	vector<vector<bool>> visited(m, vector<bool>(n, 0));
	vector<vector<Node>> parent(m, vector<Node>(n));
	Queue<Node> q;

	q.push(start); // initialize the queue
	visited[start.x][start.y] = 1; // set start been visited

	while (!q.empty()) {
		Node current = q.pop(); // the first element of queue (FIFO)
		if (current == end) {
			return backTracePath(parent);
		}

		for (int i = 0; i < 4; ++i) { // for four directions
			int nx = current.x + dx[i];
			int ny = current.y + dy[i];
			if (
				!(nx < 0 || nx >= m) &&
				!(ny < 0 || ny >= n) && // not outside of maze
				!visited[nx][ny] && // not visited yet
				maze[nx][ny] != 'x' // not wall
			) {
				q.push(Node(nx, ny)); // add to queue
				visited[nx][ny] = 1; // mark as visited
				parent[nx][ny] = current; // set parent
			}
		}
	}
	return {}; // no path found
}

vector<Node> Maze::backTracePath(const vector<vector<Node>>& parent) {
	vector<Node> path;
	Node current = end;

	// back trace from target to source
	while (!(current == start)) {
		// Convert back to 1-indexed
		path.push_back(Node(current.x + 1, current.y + 1));
		current = parent[current.x][current.y];
	}

	path.push_back(Node(start.x + 1, start.y + 1)); // Add start cell
	reverse(path.begin(), path.end());

	// for visualize the routed map
	for (int i = 2; i < path.size(); ++i) {
		if (i < 11) { // number (1~9)
			maze[path[i - 1].x - 1][path[i - 1].y - 1] = char(47 + i);
		} else { // alphabet (A~)
			maze[path[i - 1].x - 1][path[i - 1].y - 1] = char(54 + i);
		}
	}
	cout << "\n";
	drawColoredPath();
	return path;
}

void Maze::drawColoredPath() {
	for (int row = 0; row != m; ++row) {
		for (int col = 0; col != n; ++ col) {
			if (maze[row][col] != '0' && maze[row][col] != 'x') {
				SetColor(11);
			}
			cout << maze[row][col] << " ";
			SetColor();
		}
		cout << "\n";
	}
	return;
}

int main() {
	int m, n;
	cin >> m >> n;

	Maze maze(m, n);

	// key in source, target, obstacles
	for (int row = 1; row <= m; ++row) {
		int col;
		while (cin >> col && col != 0) {
			char type;
			cin >> type;
			maze.setCell(row, col, type);
		}
	}

	vector<Node> path = maze.findShortestPath();

	if (path.empty()) {
		cout << "No path found.\n";
		return 0;
	}
	// output path
	for (const auto& cell : path) {
		cout << "(" << cell.x << "," << cell.y << ")";
	}
	cout << "\n";

	return 0;
}