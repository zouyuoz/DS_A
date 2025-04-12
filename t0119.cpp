#include <iostream>

using std::cout;

int recv(int n) 
{
	if (!n) return 1;
	return 2*recv(n-1) + 3;
}

int main(){
	int aInt = 33;
	int *ptr = &aInt;
	cout << ptr << " -> ";
	++ptr;
	cout << ptr << "\n";

	char aChar = 71;
	char *ptr2 = &aChar;
	cout << static_cast<void*>(ptr2) << " -> ";
	++ptr2;
	cout << static_cast<void*>(ptr2) << "\n";
	return 0;

	int a[10] = {0,1,2};
	int* p = a;
	cout << (*p)-- << "\n";
	cout << sizeof(p) << ", " << sizeof(a) << "\n";

	int n = 5;
	cout << recv(n) << "\n";
}