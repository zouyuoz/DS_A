#include <cstdlib>
#include <iostream>
#include <ratio>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>

using std::cout;
using std::vector;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;

void insertionSort(vector<int> &vec) {
	int n = vec.size();
	for (int i = 1; i < n; ++i) {
		int y = vec[i];
		int j = i - 1;
		while (j >= 0 && vec[j] > y) {
			vec[j + 1] = vec[j];
			--j;
		}
		vec[j + 1] = y;
	}
	return;
}

void selectionSort(vector<int> &vec) {
	int n = vec.size();
	for (int i = 0; i < n; ++i) {
		int y = vec[i], k = i;
		for (int j = i + 1; j < n; ++j) {
			if (vec[j] < y) {
				y = vec[j];
				k = j;
			}
		}
		vec[k] = vec[i];
		vec[i] = y;
	}
	return;
}

void QuickSort(vector<int> &vec, int l, int r) {
	if (l >= r) return;
	int lIndex = l, rIndex = r;
	int pivot = vec[(lIndex + rIndex) / 2];

	while (lIndex <= rIndex) {
		while (vec[lIndex] < pivot) ++lIndex;
		while (vec[rIndex] > pivot) --rIndex;
		if (lIndex <= rIndex) {
			std::swap(vec[lIndex], vec[rIndex]);
			++lIndex;
			--rIndex;
		}
	}

	QuickSort(vec, l, rIndex);
	QuickSort(vec, lIndex, r);
}

void quickSort(vector<int> &vec) {
	int l = 0, r = vec.size() - 1;
	QuickSort(vec, l, r);
	return;
}

void _merge(vector<int>& vec, int l, int m, int r) {
	vector<int> temp(r - l + 1);
	int i = l, j = m + 1, k = 0;

	while (i <= m && j <= r) {
		if (vec[i] <= vec[j]) {
			temp[k++] = vec[i++];
		} else {
			temp[k++] = vec[j++];
		}
	}
	while (i <= m) {
		temp[k++] = vec[i++];
	}
	while (j <= r) {
		temp[k++] = vec[j++];
	}
	for (int p = 0; p < k; p++) {
		vec[l + p] = temp[p];
	}
	return;
}

void MergeSort(vector<int> &vec, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		MergeSort(vec, l, m);
		MergeSort(vec, m + 1, r);
		_merge(vec, l, m, r);
	}
	return;
}

void mergeSort(vector<int> &vec) {
	int l = 0, r = vec.size() - 1;
	MergeSort(vec, l, r);
	return;
}

void sift(vector<int>& vec, int start, int end) {
	int dad = start, son = 2 * dad + 1, x = vec[dad];
	while (son <= end) {
		if (son < end && vec[son] < vec[son + 1]) {
			++son;
		}
		if (x >= vec[son]) {
			break;
		}
		vec[dad] = vec[son];
		dad = son;
		son = 2 * dad + 1;
	}
	vec[dad] = x;
	return;
}

void heapSort(vector<int>& vec) {
	int n = vec.size();
	
	for (int i = n / 2 - 1; i >= 0; --i) {
		sift(vec, i, n - 1);
	}
	for (int i = n - 1; i > 0; --i) {
		std::swap(vec[0], vec[i]);
		sift(vec, 0, i - 1);
	}
	return;
}

/*
1. Insertion sort
2. Selection sort
3. Quick sort
4. Merge sort
5. Heap sort
*/

void checkAlgorithmResult(vector<int> vec) {
	for (int i = 0; i < vec.size() - 1; ++i) {
		if (vec[i + 1] < vec[i]) {
			cout << "(INVALID)\n";
			return;
		}
	}
	cout << "(valid)\n";
	return;
}

int main() {
	int numOfData = 100000;
	cout << "# of datas: " << numOfData << "\n";
	std::srand(std::time(nullptr));
	vector<int> vec;
	while (numOfData--) { vec.push_back(rand()); }
	cout << std::fixed << std::setprecision(3);

	auto measureTime = [](auto&& func, const vector<int>& vec) {
		auto copyVec = vec;
		auto t0 = steady_clock::now();
		func(copyVec);
		auto t1 = steady_clock::now();
		auto duration = duration_cast<nanoseconds>(t1 - t0).count();
		int unit = 0;
		auto durationCopy = duration;
		while (1) {
			if (durationCopy / 1000) {
				durationCopy /= 1000;
				++unit;
			}
			else break;
		}
		switch(unit) {
			case 0: { cout << duration << " ns "; break; }
			case 1: { cout << duration / 1000.0 << " us "; break; }
			case 2: { cout << duration / 1000000.0 << " ms "; break; }
			case 3: { cout << duration / 1000000000.0 << " s "; break; }
		}
		checkAlgorithmResult(copyVec);
		return;
	};

	cout << "Insertion Sort:\t"; 
	measureTime(insertionSort, vec);

	cout << "Selection Sort:\t";
	measureTime(selectionSort, vec);

	cout << "Quick Sort:\t";
	measureTime(quickSort, vec);

	cout << "Merge Sort:\t";
	measureTime(mergeSort, vec);

	cout << "Heap Sort:\t";
	measureTime(heapSort, vec);

	return 0;
}