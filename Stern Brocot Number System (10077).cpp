// Stern Brocot Number System (10077).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h> // Uncomment this line when run the program on OJ
using namespace std;

pair<int, int> parse_line(string& str) {
	int num1 = 0, num2 = 0, breakPoint = -1;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] != ' ')
			num1 = num1 * 10 + (str[i] - '0');
		else {
			breakPoint = i + 1;
			break;
		}
	}
	for (int i = breakPoint; i < str.length(); ++i)
		num2 = num2 * 10 + (str[i] - '0');
	return { num1, num2 };
}

string getPath(int& num1, int& num2) {
	string res = "";
	// Initialize the first step: 0/1, 1/1, 1/0
	int left_num1 = 0, left_num2 = 1, curr_num1 = 1, curr_num2 = 1, right_num1 = 1, right_num2 = 0;
	while (true) {
		if (curr_num1 == num1 && curr_num2 == num2)
			break;
		// If need to find target from right subtree
		if (curr_num1 * num2 < curr_num2 * num1) {
			res += 'R';
			left_num1 = curr_num1;
			left_num2 = curr_num2;
			curr_num1 += right_num1;
			curr_num2 += right_num2;
		}
		// If need to find answer from left subtree
		else {
			res += 'L';
			right_num1 = curr_num1;
			right_num2 = curr_num2;
			curr_num1 += left_num1;
			curr_num2 += left_num2;
		}
	}
	return res;
}

int main() {
	/*
	// For local test
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	if (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(line);
		myFile.close();
	}
	*/

	// For online judge
	string line;
	vector<string> text;
	while (getline(cin, line)) {
		text.push_back(line);
	}

	for (int i = 0; i < text.size(); ++i) {
		pair<int, int> curr = parse_line(text[i]);
		int num1 = curr.first, num2 = curr.second;
		if (num1 == 1 && num2 == 1) break;
		//cout << num1 << " " << num2 << endl;
		string path = getPath(num1, num2);
		cout << path << endl;
	}
	return 0;
}
