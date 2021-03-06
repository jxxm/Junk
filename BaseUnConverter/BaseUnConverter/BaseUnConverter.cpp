// BinConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Converter.h"

using namespace std;

// Expected: 1) baseAny number 2) target-base digit symbols
int main(int argc, char* argv[])
{
	if (!argv[1] || !argv[2])
	{
		return 0;
	}
	Converter converter(argv[1], argv[2]);
	cout << converter.Convert();
	return 0;
}

