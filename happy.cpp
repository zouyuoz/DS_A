#include <iostream>
#include <vector>

using std::vector;
using std::cout;

// decompose a number into its next state
int decompNum(int num) {
	int sum = 0;
	while (num) {
		// add every digit's square
		sum += (num%10)*(num%10);
		num /= 10;
	}
	return sum;
}

vector<int> path = {};

bool inPath(int const &num) {
	for (const int i: path) {
		if (i == num) return true;
	}
	return false;
}

// if a number haven't been found yet
// then dump it into this func
bool checkIfHappy(int num) {
	if (num == 1) return true;
	num = decompNum(num);
	if (inPath(num)) return false;
	path.push_back(num);
	return checkIfHappy(num);
}

void beenThrough1000Nums() {
	for (int i=1; i<=1000; ++i) {
		if (checkIfHappy(i)) {
			printf("%d\t", i);
		}
		path.clear();
	}
	return;
}

int main() {
	beenThrough1000Nums();
}