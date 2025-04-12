#include <iostream>

using namespace std;

void printBin8(int num) {
	unsigned int mask = 1 << 31;
	for (int i=0; i<32; ++i) {
		cout << ((mask & num)? 1:0);
		mask >>= 1;
	}
	cout << "\n";
}

int main() {
	int a = 64206; // 10010100~
	int b = 3120; // 10101000~
	int c = b*b;
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	printBin8(a);
	printBin8(b);
	printBin8(c);
	
	return 0;
}