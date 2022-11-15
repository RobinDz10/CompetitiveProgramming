// Vito's Family (10041).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
//#include <bits/stdc++.h> // If run program on OJ, uncomment this include
using namespace std;

vector<int> parse_line(string& line) {
	vector<int> level;
	int num = 0;
	for (int i = 0; i < line.length(); ++i) {
		if (line[i] == ' ') {
			level.push_back(num);
			num = 0;
		}
		else {
			num = num * 10 + (line[i] - '0');
			if (i == line.length() - 1) {
				level.push_back(num);
				break;
			}
		}
	}
	return level;
}

int main() {
	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			text.push_back(line);
		}
		myFile.close();
	}

	/*
	// For online(OJ) test
	string line;
	vector<string> text;
	while (getline(cin, line))
		text.push_back(line);
	*/

	int num_cases = stoi(text[0]);
	vector<int> res;
	/* Just to find median from corresponding input */
	for (int i = 1; i < text.size(); ++i) {
		vector<int> level = parse_line(text[i]);
		swap(level[0], level[level.size() - 1]);
		level.pop_back();
		int size = level.size();
		sort(level.begin(), level.end());
		if (size % 2 == 1) {
			int median = level[size / 2], ans = 0;
			for (int j = 0; j < size; ++j)
				ans += abs(level[j] - median);
			res.push_back(ans);
		}
		else {
			int median_left = level[size / 2 - 1], median_right = level[size / 2], ans1 = 0, ans2 = 0;
			for (int j = 0; j < size; ++j) {
				ans1 += abs(level[j] - median_left);
				ans2 += abs(level[j] - median_right);
			}
			res.push_back(min(ans1, ans2));
		}
	}
	for (int i = 0; i < res.size(); ++i)
		cout << res[i] << endl;
	return 0;
}