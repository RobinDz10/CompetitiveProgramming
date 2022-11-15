// Marbles (UVa 10090).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h> // Uncomment this line when run the program on OJ
using namespace std;

pair<long long, long long> parse_line(string& str) {
	long long num1 = 0, num2 = 0;
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

void reset(long long num1, long long num2, long long& x, long long& y, long long& d) {
	x = 1;
	y = 0;
	d = num1;
}

void helper(long long num1, long long num2, long long& x, long long& y, long long& d) {
	if (num2 == 0) {
		reset(num1, num2, x, y, d);
		return;
	}
	helper(num2, num1 % num2, y, x, d);
	y = -(num1 / num2) * x + y;
	return;
}

long long getBound1(long long& num, long long& x, long long& y, long long num1, long long num2) {
	long long temp1 = num * x;
	long long temp2 = num2;
	double temp = temp1 / temp2;
	long long temp3 = (long long)temp;
	double temp4 = (double)temp3;
	long long res;
	if (temp4 == temp)
		res = (long long)temp;
	else {
		if (temp <= 0.0)
			res = (long long)temp;
		else
			res = (long long)temp + 1;
	}
	return res;
}

long long getBound2(long long& num, long long& x, long long& y, long long num1, long long num2) {
	long long temp1 = num * y;
	long long temp2 = num1;
	double temp = temp1 / temp2;
	long long temp3 = (long long)temp;
	double temp4 = (double)temp3;
	long long res;
	if (temp4 == temp)
		res = (long long)temp;
	else {
		if (temp >= 0.0)
			res = (long long)temp;
		else
			res = (long long)temp - 1;
	}
	return res;
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
	// For run the program on OJ
	string line;
	vector<string> text;
	while (getline(cin, line))
		text.push_back(line);	
	*/

	int currLine = 0;
	long long x, y, d;
	for (; currLine < text.size(); ) {
		long long num = stoi(text[currLine]);
		if (num == 0) break;
		currLine++;
		pair<long long, long long> p1 = parse_line(text[currLine]);
		currLine++;
		pair<long long, long long> p2 = parse_line(text[currLine]);
		currLine++;
		long long cost1 = p1.first, num1 = p1.second, cost2 = p2.first, num2 = p2.second;
		//cout << num << " " << cost1 << " " << num1 << " " << cost2 << " " << num2 << " " << endl;
		helper(num1, num2, x, y, d);
		//long long bound1 = getBound1(num, x, y, num1, num2); // Not working correctly, due to long long size. Find a built-in function named ceil
		//long long bound2 = getBound2(num, x, y, num1, num2); // Not working correctly, due to long long size. Find a built-in function named floor
		long long bound1 = ceil((double)(-num * x) / num2);
		long long bound2 = floor((double)(num * y) / num1);
		if (num % d != 0) {
			cout << "failed" << endl;
			continue;
		}
		if (bound1 > bound2) {
			cout << "failed" << endl;
			continue;
		}
		if (cost1 * num2 >= cost2 * num1) {
			cout << x * num / d + num2 / d * bound1 << " " << y * num / d - num1 / d * bound1 << endl;
			x = x * num / d + num2 / d * bound1;
			y = y * num / d - num1 / d * bound1;
		}
		else {
			cout << x * num / d + num2 / d * bound2 << " " << y * num / d - num1 / d * bound2 << endl;
			x = x * num / d + num2 / d * bound2;
			y = y * num / d - num1 / d * bound2;
		}
	}
	return 0;
}