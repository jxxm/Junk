// TimeAdder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<string> helpCodes = { "h", "H" };
set<string> resetCodes = { "r", "R" };
set<string> exitCodes = { "q", "Q" };

bool isCode(const set<string>& codes, const string& input) {
	return codes.count(input);
}

bool isModifier(const string& input) {
	return regex_match(input, regex("x[0-9]+((.|,)[0-9]+)?"));
}

bool isTime(const string& input) {
	return regex_match(input, regex("(\\+|-)?(([0-9]+(.|,|:)([0-9]|[0-5][0-9])(.|,|:)([0-9]|[0-5][0-9]))|(([0-9]|[0-5][0-9])((.|,|:)([0-9]|[0-5][0-9]))?))"));
}

size_t getLastSeparatorPos(const string& input, const size_t pos) {
	vector<char> separators{ '.', ',', ':' };
	size_t result = input.npos;
	for (vector<char>::iterator it = separators.begin(); it != separators.end(); ++it) {
		result = input.find_last_of(*it, pos);
		if (result != input.npos) {
			break;
		}
	}
	return result;
}

void split(const string& input, vector<string>& output) {
	size_t currSeparator = input.npos;
	size_t lastSeparator = input.npos;
	string fragment;
	do {
		currSeparator = getLastSeparatorPos(input, lastSeparator);
		fragment = input.substr(
			currSeparator == input.npos
				? 0
				: currSeparator + 1, 
			lastSeparator == input.npos 
				? input.npos 
				: lastSeparator - currSeparator);
		lastSeparator = currSeparator - 1;
		output.push_back(fragment);
	} while (currSeparator != input.npos);
}

float getModifier(const string& input, const bool trustInput = false) {
	float result = 0;
	if (trustInput || isModifier(input)) {
		vector<string> fragments;
		split(input.substr(1), fragments);
		for (vector<string>::iterator it = fragments.begin(); it != fragments.end(); ++it) {
			while (result > 1) {
				result = result / 10;
			}
			result = stof(*it) + result;
		}
	}
	return result;
}

int getTime(const string& input, const bool trustInput = false) {
	int result = 0;
	int multiplier = 1;
	if (trustInput || isTime(input)) {
		vector<string> fragments;
		split(input, fragments);
		int fragment;
		for (vector<string>::iterator it = fragments.begin(); it != fragments.end(); ++it) {
			fragment = stoi(*it) * multiplier;
			result = fragment >= 0 ? fragment + result : fragment - result;
			multiplier = multiplier * 60;
		}
	}
	return result;
}

string getDisplayTime(const float input) {
	int seconds = (int)input % 60;
	int minutes = (int)(input / 60) % 60;
	int hours = (int)(input / 3600);
	return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}

void handleHelp() {
	printf("\n");
	printf("h - help\n");
	printf("r - reset\n");
	printf("q - quit\n\n");
}

void reset(float* modifier, int* time) {
	*modifier = 1;
	*time = 0;
}

int main()
{
	float modifier;
	int time;
	reset(&modifier, &time);
	string input;

	do {
		cin >> input;
		if (isCode(helpCodes, input)) {
			handleHelp();
		}
		else if (isCode(resetCodes, input)) {
			reset(&modifier, &time);
		}
		else if (isModifier(input)) {
			modifier = getModifier(input, true);
			cout << "modifier set to " << modifier << '\n';
		}
		else if (isTime(input)) {
			time = time + getTime(input, true);
			cout << "time is now " << time << '\n';
		}
		else {
			cout << "unknown input " << input << '\n';
		}
		cout << "time=" << time << ", time/modifier=" << getDisplayTime(time / modifier) << '\n';
	} while (!isCode(exitCodes, input));

	return 0;
}

