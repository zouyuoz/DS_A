#include <iostream>
#include <cmath>

using std::cout;
using std::sqrt;

// 1.
// 寫 a_n+2 = 3*a_n+1 + 15*a_n 的驗證函式
// a0 = 3; a1 = 7

class Seq {
public:
	Seq(int A0, int A1, int B0, int B1) {
		a0 = A0;
		a1 = A1;
		b0 = B0;
		b1 = B1;
		cal_rc();
		return;
	}

	int Nth(int n) const {
		if (!n) return a0;
		if (n == 1) return a1;
		int local_a0 = a0, local_a1 = a1;
		int output;
		for (int i=2; i<=n; ++i) {
			output = b0*local_a0 + b1*local_a1;
			local_a0 = local_a1;
			local_a1 = output;
		}
		return output;
	}

	float Obv(int n) const {
		return cp*pow(rp, n) + cn*pow(rn, n);
	}
private:
	int a0, a1, b0, b1;
	float rp, rn, cp, cn;

	void cal_rc() {
		// a2  - c1a1 - c0a0 = 0
		// r^2 - c1r  - c0   = 0
		// r+- = (c1 +- sqrt(c1^2 + 4c0)) / 2
		rp = (b1 + sqrt(pow(b1, 2) + 4*b0)) / 2;
		rn = (b1 - sqrt(pow(b1, 2) + 4*b0)) / 2;

		// an    = cp*(rp^n) + cn*(rn^n)
		// a0    = cp        + cn
		// a1    = cp*rp     + cn*rn
		// a0*rn = cp*rn     + cn*rn
		// a1 - a0*rn = cp*(rp-rn)
		cp = (a1 - a0*rn) / (rp - rn);
		cn = a0 - cp;
		return;
	}
};

// 2.
// 如果 b^2 - 4ac < 0 會發生甚麼事?

int main() {
	Seq a(3, -8, -3, 3);
	for (int i=2; i<=20; ++i) {
		cout << a.Nth(i) << " " << a.Obv(i) << "\n";
	}
	
	return 0;
}