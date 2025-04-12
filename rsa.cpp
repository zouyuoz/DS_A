#include <iostream>

using std::cout;
using std::cin;

int cal_phi(int const &p, int const &q) {
	return (p-1)*(q-1);
}

int find_d(int e, int phi) {
	int d = 1;
	int phi_e = phi, phi_d = phi;
	while (e != 1) {
		int multiplier = phi_e / e;
		int nextPhis[2] = {e, d};

		e = phi_e - (e * multiplier);
		d = phi_d - (d * multiplier);
		while (d < 0) {d += phi;}

		phi_e = nextPhis[0], phi_d = nextPhis[1];
	}
	return d;
}

int modEnormousNumber(int m, int e, int N) {
    int remainder = 1;  // Result of (m^e) % N
    int base = m % N;   // Reduce base mod N initially

    while (e > 0) {
        int bin = e % 2; // Get the least significant bit of e
        e /= 2;          // Right shift exponent (divide by 2)

        if (bin) {  // If the current binary bit is 1, multiply remainder
            remainder = (remainder * base) % N;
        }

        base = (base * base) % N; // Square the base at every step
    }

    return remainder;
}

int modN(int messege, int exponent, int N) {
	int number = 1;
	for (int i=0; i<exponent; ++i) {
		number *= messege;
		number %= N;
	}
	return number;
}

bool isPrime(int num) {
    if (num < 2) return false;  // 0 and 1 are not prime
    if (num == 2 || num == 3) return true;  // 2 and 3 are prime numbers
    if (num % 2 == 0 || num % 3 == 0) return false;  // Eliminate multiples of 2 and 3

    // Check divisibility from 5 to sqrt(num), skipping even numbers
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int GCD(int num1, int num2) {
	if (num2 == 0){
		return num1;
	}
	return GCD(num2, num1%num2);
}

void proper_e_value(int phi) {
	// 1. 1 < e < phi
	// 2. coprime with phi, that is, GCD(e, phi) = 1
	for (int i=2; i < phi; ++i) {
		if (GCD(phi, i) != 1) continue;
		if (!isPrime(i)) continue;
		cout << i << ", ";
	}
	return;
}

int main() {
	int a,b,c;
	while (1) {
		cin >> a>>b>>c;
		if (!a) return 0;
		cout << a << " ^ " << b << " mod " << c << " = " << modEnormousNumber(a, b, c) << "\n";
	}
	
	cout << "input two primes and a messege: ";
	int p = 5, q = 11;
	int messege = 0x0000FACE;
	cin >> p >> q >> messege;

	int phi = cal_phi(p, q);
	int N = p*q;
	cout << "N: " << N << ", phi: " << phi << "\n";
	
	cout << "choose e: ";
	int e = 7; // coprime with N, and 1 < e < phi
	cin >> e;
	int d = find_d(e, phi); // d*e (mod phi) = 1 (mod phi)
	cout << "e: " << e << ", d: " << d << "\n";

	int s = modN(messege, e, N);
	cout << "encryption: m^e mod N = s\n";
	cout << messege << " ^ " << e << " mod " << N << " = " << s << "\n";
	int decryptedMessege = modN(s, d, N);
	cout << "encryption: s^d mod N = m\n";
	cout << s << " ^ " << d << " mod " << N << " = " << decryptedMessege << "\n";
}