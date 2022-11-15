// Euclid Problem (UVa 10104).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h> //Uncomment this line when run the program on OJ
using namespace std;

pair<int, int> parse_line(string& str) {
	int num1 = 0, num2 = 0;
	int breakPoint = -1, len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ')
			num1 = num1 * 10 + (str[i] - '0');
		else {
			breakPoint = i;
			break;
		}
	}
	for (int i = breakPoint + 1; i < len; ++i)
		num2 = num2 * 10 + (str[i] - '0');
	return { num1, num2 };
}

void reset(int num1, int num2, int& x, int& y, int& d) {
	x = 1;
	y = 0;
	d = num1;
}

void helper(int num1, int num2, int& x, int& y, int& d) {
	if (num2 == 0) {
		reset(num1, num2, x, y, d);
		return;
	}
	helper(num2, num1 % num2, x, y, d);
	int temp1 = y, temp2 = x - (num1 / num2) * y;
	x = temp1;
	y = temp2;
	return;
}

int main() {
	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(line);
		myFile.close();
	}

	/*
	// For test on OJ
	string line;
	vector<string> text;
	while (getline(cin, line))
		text.push_back(line);
	*/

	for (int i = 0; i < text.size(); ++i) {
		pair<int, int> curr = parse_line(text[i]);
		//cout << curr.first << "\t" << curr.second << endl;
		int a = curr.first, b = curr.second, x, y, d;
		helper(a, b, x, y, d);
		cout << x << " " << y << " " << d << endl;
	}
	return 0;
}