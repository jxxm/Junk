// TimeAdder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

set<string> exitCodes = { "q", "Q" };
set<string> helpCodes = { "h", "H" };

bool isCode(set<string>& codes, string& input) {
	return codes.count(input);
}

void handleHelp() {
//	cout << "\nhh:mm:ss - add time\n";
//	cout << "x[number] - change modifier\n";
	cout << "h - help\n";
//	cout << "s - start/stop\n";
//	cout << "r - reset\n";
	cout << "q - quit\n\n";
}

/*
Return vector is constructed with two iterators (fist, last):
	istream_iterator constructed with input string is first,
	default constructed istream_iterator is finished by default.
*/

// copy the string? reference the string??

vector<string> split(const string& input) {
	istringstream iss(input);
	istream_iterator<string> first(iss);
	istream_iterator<string> last;
	vector<string> result(first, last);
	return result;
}

vector<string> split(const string& input, const char& delimiter) {
	vector<string> result = { "not", "implemented" };
	return result;
}

int main()
{
	handleHelp();
	string input;
	do {
		getline(cin, input);
		if (isCode(helpCodes, input)) {
			handleHelp();
		}
		else {
			vector<string> test = split(input);
			for (int i = 0; i < test.size(); ++i) {
				cout << test[i] << '\n';
			}
		}
	} while (!isCode(exitCodes, input));

	/*
	int input;
	do {
		input = getchar();
		putchar(input);
		cout << input << "\n";
	} while (!exitCodes.count(input));
	*/
	return 0;
}

