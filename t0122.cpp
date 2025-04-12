#include <iostream>
#include <vector>

using std::cout;
using std::vector;

void selectionSort(int *arr) {
	for (int i=0; i<10; ++i) {
		int maxValueIndex = i;
		int maxValue = INT_MIN;
		for (int j=i; j<10; ++j) {
			if (arr[j] > maxValue) {
				maxValueIndex = j;
				maxValue = arr[j];
			}
		}
		arr[maxValueIndex] = arr[i];
		arr[i] = maxValue;
	}
	return;
}

/*----------------------------------*/

int gcd(int A, int B) {
	if (!B) return A;
	return gcd(B, A%B);
}

class Fraction {
public:
	Fraction(int t, int b);
	void add(Fraction A);
	void outputValue() const;
private:
	int top;
	int bot;
};

Fraction::Fraction(int t, int b) {
	this->top = t;
	this->bot = b;
	return;
}

void Fraction::add(Fraction A) {
	int new_top = this->top * A.bot + A.top * this->bot;
	int new_bot = this->bot * A.bot;
	int GCD = gcd(new_top, new_bot);
	this->top = new_top / GCD;
	this->bot = new_bot / GCD;
	return;
}

void Fraction::outputValue() const {
	cout << this->top << "/" << this->bot;
	return;
}

/*------------------------*/

int fib_iter(int n) {
	if (!n) return 0;
	if (n == 1) return 1;

	int n_1 = 1, n_2 = 0; // represent a_n-1 and a_n-2
	int FIB = 0;
	for (int i=2; i<=n; ++i) {
		FIB = n_1 + n_2;
		n_2 = n_1;
		n_1 = FIB;
	}
	return FIB;
}

int fib_rcsv(int n) {
	if (!n) return 0;
	if (n == 1) return 1;

	return fib_iter(n - 1) + fib_iter(n - 2);
}

/*-----------------------*/

int returnLargestSumOfInterval(vector<int> arr) {
	int largestSum = INT_MIN;
	for (int i=0; i<arr.size(); ++i) {
		int innerLargestSum = 0;
		for (int j=i; j<arr.size(); ++j) {
			innerLargestSum += arr[j];
			if (largestSum < innerLargestSum) {
				largestSum = innerLargestSum;
			}
		}
	}
	return largestSum;
}

int main(){
	vector<int> arr = {3,-5,9,-9,-2,11,-3,5,5,2,-8,9};
	cout << returnLargestSumOfInterval(arr);
	return 0;

	Fraction A(15, 42);
	Fraction B(7, 90);
	B.add(A);
	B.outputValue();
	return 0;

	/*--------------------------*/

	int aInt[10] = {3,2,4,5,9,6,8,1,7,0};
	selectionSort(aInt);
	for (const auto t: aInt) cout << t << " ";
	return 0;
}