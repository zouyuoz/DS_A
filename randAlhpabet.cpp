#include<iostream>

using std::cout;

int main() {
	int mu[5] = {'A','E','I','O','U'};
	for (int i=1; i<=600; ++i) {
		int r='A' + rand()%36;
		if(r>90) r=mu[rand()%5];
		cout << char(r);
		if(!(i%60))cout << "\n";
	}
}