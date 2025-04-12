#include <iomanip>
#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
#include<cmath>

using std::cout;
using std::vector;

bool PROB (double prob) {
	prob = int(prob * 100);
	return prob > rand()%100;
}

class Bandit {
public:
	Bandit(double b) : prob(b) {}
	int score = 0; // how many wins from this machine
	int tried = 0; // how many times played
	void play() {
		++tried;
		if (PROB(prob)) {
			++score;
		}
		return;
	}
	double specProb() const {
		if (!tried) return 0.0;
		return double(score)/tried;
	}
	double prob;
private:
};

double cases[3][9] = {
	{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9},
	{0.01, 0.02, 0.3, 0.4, 0.5, 0.6, 0.795, 0.8, 0.805},
	{0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.05, 0.05, 0.1}
};

vector<Bandit> Bandits(int &caseNum) {
	vector<Bandit> B;
	for (int i = 0; i < 9; ++i) {
		B.push_back(Bandit(cases[caseNum][i]));
	}
	return B;
}

int findBestBandit(vector<Bandit> const &B) {
	int bestB = 0;
	double bestScore = 0;
	for (int i = 0; i < B.size(); ++i) {
		if (B[i].specProb() > bestScore) {
			bestB = i;
			bestScore = B[i].specProb();
		}
	}
	if (bestScore < 0.001) {
		return rand()%9;
	}
	return bestB;
}

void runBandit(double epsilon, vector<Bandit> &B, int time) {
	int bestBandit = rand()%9;
	for (int i=1; i<=time; ++i) {
		epsilon = pow(i, -0.2);
		if (PROB(epsilon)) {
			B[rand()%9].play();
			bestBandit = findBestBandit(B);
		} else {
			B[bestBandit].play();
		}

		if (!(i%100)) {
			for (int i=0; i<B.size(); ++i) {
				cout << i << ": " << B[i].score << "/" << B[i].tried << "=";
				cout << std::setprecision(3) << B[i].specProb() << "\t";
			}
			cout <<"\n";
		}
	}
	return;
}

int collectScore(vector<Bandit> const &B) {
	int s = 0;
	for (const auto b: B) {
		s += b.score;
	}
	return s;
}

int main(int argc, char* argv[]) {
	std::srand(std::time(NULL));
	// argv[1]: case number
	// argv[2]: try times
	// argv[3]: epsilon
	int caseNumber, time;
	double epsilon;
	if (argc > 3) {
		caseNumber = std::atoi(argv[1]);
		time = std::atoi(argv[2]);
		epsilon = std::atof(argv[3]);
	}
	else return 0;

	auto B = Bandits(caseNumber);
	runBandit(epsilon, B, time);
	for (int i=0; i<9; ++i) {
		cout << B[i].score << "/" << B[i].tried << "\n";
	}
	int score = collectScore(B);
	cout << score;

	return 0;
}
// cd "c:\Users\照元喔\source\repos\tetris\Probability\" ; if ($?) { g++ -std=c++20 imp.cpp -o imp } ; if ($?) { .\imp 0 1000 0.2}