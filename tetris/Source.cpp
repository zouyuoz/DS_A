#include<iostream>

using namespace std;


void initialScreen() {
	cout << "| . .t.e.t.r.i.s. . .|\n";
	return;
}
int main() {
	cout << "| . . . . . . .[][] .|\n";
	cout << "| .[][][] . . . .[][]|\n";
	cout << "| . .[] . . .[] . . .|\n";
	cout << "| . . . .[][][] . . .|\n";
	int b = 10000;
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < b; j++) {
			int c = 2 * i - j;
		}
	}
}