// Programming Assignment 1: Define New Data Type (New Object)
// Author: Z.Y.Qio
// ID: 110610013
// (I've learned object oriented programming so some functions I'll use OOP concepts)

#include <iostream>
#include <stdio.h>
#include <string>

using std::string;
using std::cout;

class Date {
public:
	Date();
	Date(int, int, int); 		// year, month, day
	int daysFromOrigin() const; // Origin is 0001/01/01, Monday
	friend std::ostream& operator <<(std::ostream &os, const Date &date);
	void outputDateWithWeek();	// also another function that outputs date
private:
	int y, m, d;
	string getMonthString() const;	// return a string of the month of this Date
	string dayOfWeek() const;		// return a string of the week day of this Date
};

std::ostream& operator <<(std::ostream &os, const Date &date) {
	os << date.getMonthString() << " " << date.d << ", " << date.y;
	return os;
}

void Date::outputDateWithWeek() {
	cout << *this << " is " << dayOfWeek() << "\n";
	return;
}

string Date::getMonthString() const {
	string months[12] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};
	return months[m - 1];
}

string Date::dayOfWeek() const {
	string weekDay[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	// start from Monday because 0001/01/01 is Monday.
	return weekDay[daysFromOrigin() % 7];
}

bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month) {
	int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && isLeapYear(year)) {
		return 29;
	}
	return daysPerMonth[month - 1];
}

// doesn't work if that date is before 0001/01/01 (aka BC)
int Date::daysFromOrigin() const {
	int totalDays = 0;
	for (int year = 1; year < y; ++year) { totalDays += isLeapYear(year) ? 366 : 365; }
	for (int month = 1; month < m; ++month) { totalDays += daysInMonth(y, month); }
	totalDays += d - 1;

	return totalDays;
}

void DateSub() {
	Date date1;
	string s; std::cin >> s;
	Date date2;
	int daysSub = std::abs(date1.daysFromOrigin() - date2.daysFromOrigin());
	cout << daysSub << " days from " << date1 << " to " << date2 << "\n";
	return;
}

void DateAdd() {
	Date date;
	int days;
	scanf_s(" + %d", &days);
	int y = 0, m = 0, d = date.daysFromOrigin() + days;
	while (++y) {
		int daysOfThisYear = isLeapYear(y) ? 366 : 365;
		d -= daysOfThisYear;
		if (d < 0) {
			d += daysOfThisYear;
			break;
		}
	}
	while (++m) {
		int daysOfThisMonth = daysInMonth(y, m);
		d -= daysOfThisMonth;
		if (d < 0) {
			d += daysOfThisMonth;
			break;
		}
	}
	d += 1;
	Date dateAdded(y, m, d);
	cout << days << " days after " << date << " is " << dateAdded << ".\n";
	return;
}

Date::Date() { scanf_s("%d/%d/%d", &y, &m, &d); }

Date::Date(int y, int m, int d): y(y), m(m), d(d) {}

int main() {
	cout << "first input: enter a date\n";
	Date date_A;
	date_A.outputDateWithWeek();

	cout << "second input: subtraction of two dates\n";
	DateSub();

	cout << "third input: addition to a date\n";
	DateAdd();
	
	return 0;
}