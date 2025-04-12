#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>

std::knuth_b rand_engine;  // replace knuth_b with one of the engines listed below

bool random_bool_with_prob( double prob )  // probability between 0.0 and 1.0
{
    std::bernoulli_distribution d(prob);
    return d(rand_engine);
}

std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);

bool random_bool_prob( double prob )  // probability between 0.0 and 1.0
{
    return uniform_zero_to_one(rand_engine) > prob;
}

using std::cout;

const float GR = (std::sqrt(5) - 1)/2;
const float e_ = std::exp(-1);

void sort(int* a, int size) {
	// selection
	for (int i=0; i<size; ++i) {
		int min=INT_MAX;
		int index=i;
		for (int j=i; j<size; ++j) {
			if (a[j]<min) {
				min = a[j];
				index = j;
			}
		}
		int temp = a[i];
		a[i] = a[index];
		a[index] = temp;
	}
	return;
}

bool trueWithProbability(float p) {
	if (p > 1.0 || p < 0.0) return 0;
    int p100 = p*100;
	return rand()%100 < p100;
}

int triesToGetPrecision6(double p, int& count, double value = 1048570) {
	if (value <= 1) {
        // cout << "p = " << p << ":\t" << count << "\n";
        return count;
	}
	value *= random_bool_prob(p) ? p: 1-p;

	count = triesToGetPrecision6(p, ++count, value);
	return count;
}

int fvRat(int* a, int size, int value, float ratio){
	int lowBound = 0;
	int highBound = size;
	int tries = 0;
	
	while (highBound != lowBound) {
		int index = lowBound + std::max(int((highBound - lowBound)*ratio), 1);
		// cout << index << ", " << lowBound << ", " << highBound << "\n";
		if (a[index] == value) {
			return tries;
		}
		(a[index] > value ? highBound : lowBound) = index;
		++tries;
		// system("Pause");
	}

	cout << "No found\n";
	return -1;
}

//7776

int A() {
int size = 100000;
	int* a = new int[size];
	srand(1);
	for (int i=0; i<size; ++i) {
		a[i] = i;
	}
	// sort(a, size);
	for (int i=0; i<size - 1; ++i) {
		if (a[i] > a[i+1]) return 0;
	}
	
	int testAmount = size;
	int tries[7] = {0};
	int SumTries[7] = {0};
	float ratio[7] = {1.0/3, e_, 1-GR, 0.5, GR, 1-e_, 2.0/3};
	for (int i=1; i<testAmount; ++i) {
		int index = 0;
		for (auto const r: ratio) {
			tries[index] = fvRat(a, size, i, r);
			if (tries[index] > 0) SumTries[index] += tries[index];
			++index;
		}

		// cout << "value: " << i << "\t" << bin << "\t" << terl << "\t" << terr << "\n";
	}

	cout << "Average:\n";
	for (auto const sum: SumTries) {
		cout << float(sum)/testAmount << "\t";
	}

	delete [] a;
	return 0;
}

int mainbb() {
	srand(time(NULL));
	// float ratio[7] = {1.0/3, e_, 1-GR, 0.5, GR, 1-e_, 2.0/3};
	int testAmount = 10000;
	for (double p = 0.1; p <= 0.91; p += 0.02) {
		float sum = 0;
		for (int i=0; i<testAmount; ++i) {
			int tries = 0;
			sum += triesToGetPrecision6(p, tries);
		}
		sum /= testAmount;
		cout << p << " " << sum << "\n";
	}
	
	return 0;
}

int main() {
	srand(time(NULL));
	int totalDiff=0;
	for (double p = 0.01; p < 1; p += 0.01) {
		int a=0;
		for (int i=0; i<10000; ++i) {
			if (trueWithProbability(p)) ++a;
		}
		cout << p << " " << a << " " << abs(10000*p - a) << "\n";
		totalDiff += abs(10000*p - a);
	}
	cout << "totalDiff: " << totalDiff;
	return 0;
}