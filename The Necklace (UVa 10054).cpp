// The Necklace (UVa 10054).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h> // Uncomment this line when run the program on OJ
using namespace std;

vector<int> parse_line(string& str) {
	int num1 = 0, num2 = 0, len = str.length(), breakPoint = -1;
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

void helper(int curr, vector<vector<int>>& beads, vector<int>& color) {
	for (int i = 1; i <= 50; ++i) {
		if (beads[curr][i]) {
			beads[curr][i]--;
			beads[i][curr]--;
			helper(i, beads, color);
			cout << i << " " << curr << endl;
		}
	}
}

int main() {
	/*
	// For test locally
	fstream myFile("Input.txt");
	string line;
	vector<string> text;
	while (myFile.is_open()) {
		while (getline(myFile, line))
			text.push_back(line);
		myFile.close();
	}
	*/
	
	// For run the program on OJ
	string line;
	vector<string> text;
	while (getline(cin, line))
		text.push_back(line);

	int currLine = 0;
	int num_Cases = stoi(text[currLine++]);
	for (int num = 1; num <= num_Cases; ++num) {
		cout << "Case #" << num << endl;

		int num_Beads = stoi(text[currLine++]);
		vector<vector<int>> beads(1001, vector<int>(1001, 0));
		vector<int> color(1001, 0);
		for (int i = 1; i <= num_Beads; ++i) {
			vector<int> level = parse_line(text[currLine++]);
			int color1 = level[0], color2 = level[1];
			beads[color1][color2]++;
			beads[color2][color1]++;
			color[color1]++;
			color[color2]++;
		}
		int canArrange = 0;
		for (int i = 1; i <= 50; ++i) {
			if (color[i] % 2) {
				cout << "some beads may be lost" << endl;
				canArrange = 1;
				break;
			}
		}
		if (canArrange) {
			cout << endl;
			continue;
		}
		for (int i = 1; i <= 50; ++i) {
			if (color[i]) {
				helper(i, beads, color);
				break;
			}
		}
		cout << endl;
	}
	return 0;
}