// Midterm-Problem2.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

pair<int, int> parseParameters(string& str) {
	int n = 0, k = 0, breakPoint = -1, len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ')
			n = n * 10 + (str[i] - '0');
		else {
			breakPoint = i;
			break;
		}
	}
	for (int i = breakPoint + 1; i < len; ++i)
		k = k * 10 + (str[i] - '0');
	return { n, k };
}

vector<int> parseSet(string& str) {
	vector<int> subset;
	int len = str.length(), num = 0;
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ') {
			num = num * 10 + (str[i] - '0');
			if (i == len - 1) {
				subset.push_back(num);
				break;
			}
		}
		else {
			subset.push_back(num);
			num = 0;
		}
	}
	return subset;
}

int helper(vector<int>& vec) {
	int res = 0, size = vec.size();
	sort(vec.begin(), vec.end());
	for (int i = size - 1; i >= 0; --i) {
		if (vec[i] % 2 == vec[size - 1] % 2)
			res += pow(2, vec[i] + 1) - 1;
		else
			res -= pow(2, vec[i] + 1) - 1;
	}
	return res;
}

void output(int index, int num) {
	cout << index << ": ";
	int temp = (num / 2) ^ num;
	int i = 0;
	while (temp) {
		if (temp % 2)
			cout << i << " ";
		temp /= 2;
		i += 1;
	}
	cout << endl;
}

int main() {
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(line);
		myFile.close();
	}
	
	int num_cases = stoi(text[0]), currLine = 1;
	for (int i = 0; i < num_cases; ++i) {
		pair<int, int> p = parseParameters(text[currLine]);
		currLine++;
		int n = p.first, k = p.second;
		vector<int> vec;
		for (int j = 0; j < n; ++j)
			vec.push_back(i);
		vector<int> subset = parseSet(text[currLine]);
		currLine++;
		int start = helper(subset);
		int total = pow(2, n);
		for (int j = 0; j < total; ++j)
			output(j, (start + j) % total);
		cout << endl;
	}
	return 0;
}