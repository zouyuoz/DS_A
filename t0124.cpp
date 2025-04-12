#include <iostream>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::string;

void selectionSort(int* arr, int len) {
	// select the min from i to len
	for (int i=0; i<len; ++i) {
		int minIdx = i;
		int min = arr[minIdx];
		for (int j=i+1; j<len; ++j) {
			if (arr[j] < min) {
				minIdx = j;
				min = arr[minIdx];
			}
		}
		// now we found min from i to len
		// swap it from i and minIdx
		std::swap(arr[i], arr[minIdx]);
	}
	return;
}

void insertionSort(int* arr, int len) {
	// select each arr[i] and insert into 0~i-1
	for (int i=1; i<len; ++i) {
		int hold = arr[i];
		int insertIdx = i;
		while (insertIdx && arr[insertIdx-1] > hold) {
			arr[insertIdx] = arr[insertIdx-1];
			--insertIdx;
		}
		arr[insertIdx] = hold;
	}
	return;
}

void bubbleSort(int* arr, int len) {
	// let big number sink to bottom
	int lastSwap = 1;
	while (len > 1) {
		for (int j=0; j<len-1; ++j) {
			if (arr[j] > arr[j+1]) {
				lastSwap = j+1;
				std::swap(arr[j], arr[j+1]);
			}
		}
		len = lastSwap;
	}
	return;
}

void rearrangeString(string L, string current = "") {
	if (!L.size()) {
		cout << current << "\n";
		return;
	}
	for (int i=0; i<L.size(); ++i) {
		char head = L[i];
		string remain = L.substr(0, i) + L.substr(i+1);
		rearrangeString(remain, current + head);
	}
	return;
}

int findMedian(float* wArr, int len) {
	int low = 0, high = len;
	int pivot = 0;
	while (high - low > 1) {
		pivot = (low + high)/2;
		float sumf = 0;
		for (int i=0; i<pivot; ++i) {
			sumf += wArr[i];
		}
		if (sumf < 0.5) {
			// which means is valid
			// but should explore more
			low = pivot;
		} else {
			// means sum is invalid
			// should lower the pivot
			high = pivot;
		}
		cout << pivot;
		system("PAUSE");
	}
	return pivot;
}

void QuickSort(int *vec, int l, int r) {
	if (l >= r) return;
	cout << "l: " << l << ". r: " << r << "\n";
	int lIndex = l, rIndex = r;
	int pivot = vec[l];
	while (lIndex <= rIndex) {
		while (vec[lIndex] < pivot) ++lIndex;
		while (vec[rIndex] > pivot) --rIndex;

		if (lIndex > rIndex) break;
		std::swap(vec[lIndex], vec[rIndex]);
		++lIndex;
		--rIndex;

		cout << "lI:" << lIndex << ". rI:" << rIndex << " => ";
		for (int i=l; i<=r; ++i) {cout << vec[i];}
		cout << "\n";
	}
	cout << "final l: " << l << ". r: " << r << ". lI: " << lIndex << ". rI: " << rIndex << "\n";
	QuickSort(vec, l, rIndex);
	QuickSort(vec, lIndex, r);
}

void pivot(int* arr, int l, int r) {
	int pivot = arr[l];
	int swapIndex = l;
	for (int i=l + 1; i <= r; ++i) {
		if (pivot > arr[i]) {
			++swapIndex;
			cout << "swap: " << i << ", "<< swapIndex << ": ";
			std::swap(arr[swapIndex], arr[i]);
			for (int k=l; k<=r; ++k) cout << arr[k];
			cout << "\n";
		}
	}
	std::swap(arr[swapIndex], arr[l]);
	for (int k=l; k<=r; ++k) cout << arr[k];
	cout << "\n";
}

int myWay(int n) {
	int fib[2] = {0, 1};
	if (n<2) { return fib[n]; }
	for (int i=2; i<=n; ++i) {
		int temp = fib[1];
		fib[1] += fib[0];
		fib[0] = temp;
	}
	return fib[1];
}

template<typename T>
class Node {
public:
    T data;
    Node* next = nullptr;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Linklist {
private:
    Node<T>* head;
	int length = 0;

public:
    Linklist() : head(nullptr) {}

    ~Linklist() {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
		length = 0;
    }

    void insert(T value) {
        // to the head
		Node<T>* newHead = new Node<T>(value);
		newHead->next = head;
		head = newHead;
		++length;
		return;
    }

	int getLength() { return length; }

	void insert(T value, int where) {
		// to specific position
		if (where > length || where < 0) {
			cout << "insert at " << where << " is invalid.\n";
			return;
		}
		if (!where) {
			insert(value);
			return;
		}
		Node<T>* cursor = head;
		for (int i=1; i<where; ++i) {
			cursor = cursor->next;
		}
		Node<T>* newElement = new Node<T>(value);
		newElement->next = cursor->next;
		cursor->next = newElement;
		++length;
		return;
	}

    void printList() {
        // from head to tail
		Node<T>* cursor = head;
		while (cursor) {
			cout << cursor->data << " ";
			cursor = cursor->next;
		}
		cout << "\n";
		return;
    }
};


#include <chrono>

void maxIntervalSumWithBreak(int* arr) {
	int maxSum = 0;
	for (int i=0; i<64; ++i) {
		int innerSum = 0;
		for (int j=i; j<64; ++j) {
			innerSum += arr[j];
			if (innerSum < 0) break;
			if (innerSum > maxSum) { maxSum = innerSum; }
		}
	}
	cout << maxSum << "\n";
	return;
}

// Function to measure execution time
template <typename Func>
void measureExecutionTime(Func function) {
    auto start = std::chrono::high_resolution_clock::now(); // Start time
    function();  // Call the function
    auto end = std::chrono::high_resolution_clock::now(); // End time

    // Calculate duration in microseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
}

void maxIntervalSum(int* arr) {
	int maxSum = 0;
	for (int i=0; i<64; ++i) {
		int innerSum = 0;
		for (int j=i; j<64; ++j) {
			innerSum += arr[j];
			if (innerSum > maxSum) { maxSum = innerSum; }
		}
	}
	cout << maxSum << " ";
	return;
}

int* createArr64() {
	int* arr = new int[64];
	for (int i=0; i<64; ++i){
		arr[i] = rand()%64;
		if (rand()%2) arr[i] *= -1;
	}
	return arr;
}

template <typename Func>
void doFunc100(Func function) {
	for (int i=0; i<100; ++i) {
		function();
	}
	return;
}

class Brian {
public:
	void Public() { cout << "Brain Public\n"; }
private:
	void Private() { cout << "Brain Private\n"; }
protected:
	void Protected() { cout << "Brain Protected\n"; }
};

class Diana : Brian {
public:
	void DPublic() { cout << "Diana Public\n"; }
	void DianaDo() { Protected(); Public(); }
private:
	void DPrivate() { cout << "Diana Private\n"; }
protected:
	void DProtected() { cout << "Diana Protected\n"; }
};

int main() {
	int A = 0x00000092;
	int B = 0x00000035;
	int C = A ^ B;
	cout << C;
}