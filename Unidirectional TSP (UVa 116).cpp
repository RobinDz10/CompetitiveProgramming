// Unidirectional TSP (UVa 116).cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<int> parse_line(string& str) {
	vector<int> vec;
	int num = 0, len = str.length();
	for (int i = 0; i < len; ++i) {
		if (str[i] != ' ') {
			num = num * 10 + (str[i] - '0');
			if (i == len - 1) {
				vec.push_back(num);
				break;
			}
		}
		else {
			vec.push_back(num);
			num = 0;
		}
	}
	return vec;
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

	int currLine = 0;
	while (currLine < text.size()) {
		vector<int> boardSize = parse_line(text[currLine++]);
		int rows = boardSize[0], cols = boardSize[1];
		vector<vector<int>> board;
		for (int i = 0; i < rows; ++i) {
			vector<int> level = parse_line(text[currLine++]);
			board.push_back(level);
		}
		vector<vector<int>> costs(rows, vector<int>(cols, INT_MAX));
		for (int i = 0; i < cols; ++i) {

		}
	}
	return 0;
}