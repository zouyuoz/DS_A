#include<iostream>

#include<cmath>

using namespace std;

int main() {
	double e = exp(1);

	double min = 0.002;
	double theMin = 1;

	for (int i=2; i<200; ++i) {
		for (int j=i; j<200; ++j) {
			double a = double(j)/ i;
			if (abs(a - e) <= min) {
				cout << i << ", " << j << "\t" << a << "\t" << abs(a-e);
				if (abs(a-e) < theMin) {
					cout << "\tV";
					theMin = abs(a-e);
				}
				cout << "\n";
			}
		}
	}
}