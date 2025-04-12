#include <cmath>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;

void test(const int &num) {
	static int a = 0;
	a += num;
	cout << a << "\n";
}

int a = 0;

void bin(int *a, int l, int r, int target) {
	if (l >= r) {
		cout << "no found.\n";
		return;
	}
	int pivot = (l+r)/2;
	if (a[pivot] == target) {
		cout << "found " << a[pivot] << "\n";
		return;
	}
	else if (a[pivot] < target) l = pivot+1;
	else r = pivot;
	return bin(a, l, r, target);
}

void findSumValid(int num) {
	for (int i=0; i<=num/2; ++i) {
		int sum = 0;
		for (int j=i; j<num; ++j) {
			sum += j;
			if(sum == num) {
				cout << i << ", " << j << "\n";
				// return;
			}
		}
	}
	cout << "No\n";
	return;
}

void findMax3(int* a, int len) {
	int max = 0;
	for (int mask=0; mask<1<<len; ++mask) {
		// for example, len = 5 then
		// mask range from 00000 to 11111
		int sum = 0;
		int maskCopy = mask;
		int bit = 0;
		while (maskCopy) {
			if (maskCopy & 1) sum += a[bit];
			maskCopy >>= 1;
			++bit;
		}
		if (sum > max && sum%3 == 0) max = sum;
	}
	cout << max << "\n";
	return;
}

int main() {
	int arr[10] = {3,6,5,1,8,6,4,1,3,2};
	findMax3(arr, 10);
	// findSumValid(127);
	// findSumValid(265);
	return 0;
}